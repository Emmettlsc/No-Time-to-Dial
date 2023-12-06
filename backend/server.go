package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"github.com/google/uuid"
	"github.com/gorilla/websocket"
	"log"
	"net/http"
	"sync"
)

var addr = flag.String("addr", "0.0.0.0:8080", "http service address")

var upgrader = websocket.Upgrader{
	CheckOrigin: func(r *http.Request) bool {
		return true
	},
}

type client struct {
	conn *websocket.Conn
	send chan []byte
	id   uuid.UUID
}

var (
	clients   = make(map[*client]bool) // Connected clients
	broadcast = make(chan []byte)      // Broadcast channel
	mu        sync.Mutex               // Mutex for clients
)

// ClientMessage represents a message along with the client's ID
type ClientMessage struct {
	ID      string `json:"id"`
	Message string `json:"message"`
}

// NameUpdate represents a name update message
type NameUpdate struct {
	UUID string `json:"uuid"`
	Name string `json:"name"`
}

func echo(w http.ResponseWriter, r *http.Request) {
    conn, err := upgrader.Upgrade(w, r, nil)
    if err != nil {
        log.Print("upgrade:", err)
        return
    }
    defer conn.Close()

    tmpid, _ := uuid.NewUUID()

    cl := &client{conn: conn, send: make(chan []byte, 256), id: tmpid}
    mu.Lock()
    clients[cl] = true
    mu.Unlock()

    go writePump(cl)

    for {
        _, message, err := conn.ReadMessage()
        if err != nil {
            if websocket.IsUnexpectedCloseError(err, websocket.CloseGoingAway, websocket.CloseAbnormalClosure) {
                log.Printf("error: %v", err)
            }
            break
        }

        // Attempt to unmarshal message as a name update
        var nameUpdate NameUpdate
        if err := json.Unmarshal(message, &nameUpdate); err == nil && nameUpdate.UUID != "" {
            // Handle name update
            updatedMessage, err := json.Marshal(nameUpdate)
            if err != nil {
                log.Printf("json marshal error: %v", err)
                continue
            }
            broadcast <- updatedMessage
            continue
        }

        // Handle as a normal message if not a name update
        clientMessage := ClientMessage{
            ID:      cl.id.String(),
            Message: string(message),
        }
        jsonMessage, err := json.Marshal(clientMessage)
        if err != nil {
            log.Printf("json marshal error: %v", err)
            continue
        }
        broadcast <- jsonMessage
    }

    mu.Lock()
    delete(clients, cl)
    close(cl.send)
    mu.Unlock()
}

func handleMessages() {
	for {
		msg := <-broadcast
		fmt.Printf("Broadcasting message: %s\n", string(msg))
		mu.Lock()
		for cl := range clients {
			select {
			case cl.send <- msg:
			default:
			}
		}
		mu.Unlock()
	}
}

func writePump(cl *client) {
	defer cl.conn.Close()
	for {
		msg, ok := <-cl.send
		if !ok {
			cl.conn.WriteMessage(websocket.CloseMessage, []byte{})
			return //exit when send channel is closed
		}
		if err := cl.conn.WriteMessage(websocket.TextMessage, msg); err != nil {
			log.Println("write error:", err)
			return
		}
	}
}

func main() {
	flag.Parse()
	log.SetFlags(0)
	http.HandleFunc("/ws", echo)
	go handleMessages()

	log.Fatal(http.ListenAndServe(*addr, nil))
}

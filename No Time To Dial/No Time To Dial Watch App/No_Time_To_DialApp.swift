//
//  No_Time_To_DialApp.swift
//  No Time To Dial Watch App
//
//  Created by Emmett Cocke on 11/18/23.
//

import SwiftUI
import Foundation

@main
struct No_Time_To_Dial_Watch_AppApp: App {
    @StateObject var itemListModel = ItemListModel()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(itemListModel)
        }
    }
}

struct ParsedMessage: Identifiable, Decodable, Hashable {
    let id: UUID
    var message: String
}
//struct ParsedMessage: Identifiable, Decodable, Hashable {
//    let id: UUID
//    var deviceName: String
//    var message: String
//}


struct ListItem: Identifiable, Hashable {
    let id = UUID()
    
    var description: String
    
    init(_ description: String) {
        self.description = description
    }
}

class ItemListModel: NSObject, ObservableObject {
    @Published var items = [String: String]()
    @Published var devices = [String: [String]]() // Changed from 'items' to 'devices'

    
    private var websocketManager: WebSocketManager?

    override init() {
           super.init()
           websocketManager = WebSocketManager { [weak self] receivedJSON in
               guard let self = self,
                     let data = receivedJSON.data(using: .utf8),
                     let parsedMessage = try? JSONDecoder().decode(ParsedMessage.self, from: data) else {
                   return
               }
               DispatchQueue.main.async {
                   let deviceName = "test"//parsedMessage.deviceName
                   if var existingMessages = self.devices[deviceName] {
                       existingMessages.append(parsedMessage.message)
                       self.devices[deviceName] = existingMessages
                   } else {
                       self.devices[deviceName] = [parsedMessage.message]
                   }
               }
           }
           websocketManager?.connect()
    }


    deinit {
        websocketManager?.disconnect()
    }
}

class WebSocketManager {
    private var webSocketTask: URLSessionWebSocketTask?
    private let onDataReceived: (String) -> Void
//    private var url = URL(string: "ws://52.202.91.145:8080/echo")!

//    private var url = URL(string: "ws://localhost:8080/echo")!
    private var url = URL(string: "wss://snow.bazzled.com/ws")!
    init(onDataReceived: @escaping (String) -> Void) {
        self.onDataReceived = onDataReceived
    }
    
    func connect() {
        print("GOT HERE")
        let session = URLSession(configuration: .default)
        webSocketTask = session.webSocketTask(with: url)
        webSocketTask?.resume()
        listenForMessages()
    }
    
    private func listenForMessages() {
        webSocketTask?.receive { [weak self] result in
            switch result {
            case .failure(let error):
                print("Error in receiving message: \(error)")
            case .success(let message):
                switch message {
                case .string(let text):
                    print("Received string: \(text)")
                    DispatchQueue.main.async {
                        self?.onDataReceived(text)
                    }
                case .data(let data):
                    print("Received data: \(data)")
                
                @unknown default:
                    fatalError()
                }
                
                self?.listenForMessages()//continue listening for messages
            }
        }
    }
    
    func disconnect() {
        webSocketTask?.cancel(with: .normalClosure, reason: nil)
    }
}

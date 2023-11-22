//NOTE: i took a lot of the networking for this project from the websocketclient example by Markus Sattler (an example in the dropdown)

#define _WEBSOCKETS_LOGLEVEL_     2
#define WEBSOCKETS_NETWORK_TYPE   NETWORK_WIFININA

#include <WiFiNINA_Generic.h>
#include <Arduino_LSM6DS3.h>
#include <WebSocketsClient_Generic.h>

WebSocketsClient webSocket;

int status = WL_IDLE_STATUS;

#define USE_SSL         false
// #define WS_SERVER           "ec.bazzled.com"
#define WS_SERVER           "54.153.78.201"
#define WS_PORT             80

char ssid[] = "UCLA_WEB";
char pass[] = "";

bool alreadyConnected = false;

float ax, ay, az;
float initAX, initAY, initAZ;
String letterCode = "";
unsigned long startTime;
// morse code array
String keys[] = {"01", "1000", "1010", "100", "0", "0010", "110", "0000", "00", "0111", "101", "0100", "11", "10", "111", "0110", "1101", "010", "000", "1", "001", "0001", "011", "1001", "1011", "1100", "01111", "00111", "00011", "00001", "00000", "10000", "11000", "11100", "11110", "11111"};
int sizeOfKeysArray = sizeof(keys)/sizeof(keys[0]);
// characters array
String values[] = {"A", "B", "C", "D" , "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "X", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  while (!Serial);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");

    // don't continue
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 3 seconds for connection:
    delay(3000);
  }

  printWifiStatus();

  // server address, port and URL
  Serial.print("WebSockets Server : ");
  Serial.println(WS_SERVER);

  // server address, port and URL
  webSocket.begin(WS_SERVER, WS_PORT, "/echo");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // server address, port and URL
  Serial.print("Connected to WebSockets Server @ ");
  Serial.println(WS_SERVER);

    if (!IMU.begin()) {
      Serial.println("Failed to initialize IMU!");
      while (1);
  }
  
    // obtain initional imu acceleration data for calibration
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(initAX, initAY, initAZ);
  }
    startTime = millis();
}


void loop() {
    int letterCodeLength = letterCode.length();
    webSocket.loop();

    static unsigned long lastSendTime = 0;
    unsigned long currentMillis = millis();

    //data send every ,1 secs 
    if (currentMillis - lastSendTime > 100) {
        lastSendTime = currentMillis;

        if (IMU.accelerationAvailable()) {
          IMU.readAcceleration(ax, ay, az);


          // check if the initial IMU Z-value is greater than zero...
          if (initAZ > 0){
            // if the initial IMU Z-value is greater than zero then check for the turn in the opossite Z-direction
            if (az < 0) {
              // inialize the start time of the interaction or turn
              unsigned long triggerTime = millis();
              // while the IMU sensor did not sense a turn back to the original positon keep updating and reading the IMU Z-value
              while (az < 0) {
                if (IMU.accelerationAvailable()) {
                  IMU.readAcceleration(ax, ay, az);
                }
              }
              // check the current time and calculate the amount of time that it took to turn back to the original position
              unsigned long releaseTime = millis();
              unsigned long timeDiff = releaseTime - triggerTime;
              // if the time is greater than 400 milliseconds then it siganls a "1" which represents a dash
              if (timeDiff > 400) {
                letterCode = letterCode + "1";
              // else if the time is less then or equal to 400 milliseconds then it signals a "0" which represents a dot
              } else {
                letterCode = letterCode + "0";
              }
              // set the startTime to the current time
              startTime = millis();
            }
          
          // checks the opposite directionl turn 
          } else {
            if (az > 0) {
              unsigned long triggerTime = millis();
              while (az > 0) {
                if (IMU.accelerationAvailable()) {
                  IMU.readAcceleration(ax, ay, az);
                }
              }
              unsigned long releaseTime = millis();
              unsigned long timeDiff = releaseTime - triggerTime;
              if (timeDiff > 400) {
                letterCode = letterCode + "1";
              } else {
                letterCode = letterCode + "0";
              }
              startTime = millis();
            } 
          }

        // unsigned long stopTime = millis();
        // unsigned long pauseTime = stopTime - startTime;



        unsigned long stopTime = millis();
        unsigned long pauseTime = stopTime - startTime;
        if ((letterCodeLength > 0) && (letterCodeLength == letterCode.length()) && (pauseTime > 2000)) {
          String result = getValue(keys, values, letterCode);
          Serial.println(letterCode);
          Serial.println(result);
          startTime = millis();
          letterCode = "";
          
          // String jsonMessage = "{\"type\": \"char\", \"value\": " + String(result) + "}";

          //snd msg via websocket
          webSocket.sendTXT(String(result));
        }


      }
    }
}

// function used to get value of an associated key
String getValue(String keys[], String values[], String key) {
  for (int i = 0; i < sizeOfKeysArray; i++) {
    if (keys[i] == key) {
      return values[i];
    }
  }
  // Return "unknown" if the key is not found
  return "unknown";
}

void webSocketEvent(const WStype_t& type, uint8_t * payload, const size_t& length)
{
    switch (type)
    {
        case WStype_DISCONNECTED:
            if (alreadyConnected)
            {
                Serial.println("[WSc] Disconnected!");
                alreadyConnected = false;
            }
            break;

        case WStype_CONNECTED:
            {
                alreadyConnected = true;
                Serial.print("[WSc] Connected to url: ");
                Serial.println((char *) payload);
                // send a message to server when Connected
                webSocket.sendTXT("Connected");
            }
            break;

        case WStype_TEXT:
            // Log the received text message
            Serial.print("[WSc] Received text: ");
            Serial.println((char *) payload);
            // Optionally, handle received text messages here
            break;

        case WStype_BIN:
            // Log binary messages (if needed)
            Serial.print("[WSc] Received binary length: ");
            Serial.println(length);
            // Optionally, handle binary data here
            break;

        case WStype_PING:
            // Log ping messages (if needed)
            Serial.println("[WSc] Received ping");
            break;

        case WStype_PONG:
            // Log pong messages (if needed)
            Serial.println("[WSc] Received pong");
            break;

        default:
            break;
    }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("WebSockets Client IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
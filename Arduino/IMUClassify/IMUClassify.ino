// file IMUClassify.ino

#include <Arduino_LSM6DS3.h>
#include "Pipeline.h"
#include "Classifier.h"
#include "GestureClassification.h"

#define _WEBSOCKETS_LOGLEVEL_ 2
#define WEBSOCKETS_NETWORK_TYPE NETWORK_WIFININA

#include <WiFiNINA_Generic.h>
#include <Arduino_LSM6DS3.h>
#include <WebSocketsClient_Generic.h>

WebSocketsClient webSocket;

int status = WL_IDLE_STATUS;

#define USE_SSL false
// #define WS_SERVER asd          "ec.bazzled.com"
#define WS_SERVER "184.72.14.50"
#define WS_PORT 8080

char ssid[] = "UCLA_WEB";
char pass[] = "";

bool alreadyConnected = false;

unsigned long startTime;

// int buf_idx = 0;
// const int N = 4;
// int buffer[N];
// int curr_target = -1;
// int prev_target = -1;
// int prev_prev_target = -1;

void setup() {
  Serial.begin(115200);
  Serial.println("Started");

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");

    // don't continue
    while (true)
      ;
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
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
  webSocket.begin(WS_SERVER, WS_PORT, "/ws");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // server address, port and URL
  Serial.print("Connected to WebSockets Server @ ");
  Serial.println(WS_SERVER);


  while (!IMU.begin()) 
    Serial.println("Failed to initialize IMU!");

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
  startTime = millis();
}

// enum actions {
//   error = -1,
//   neutral,
//   clockwise,
//   counterclockwise,
//   horizontal_shake,
//   vertical_shake
// };

// enum states {
//   wait1,
//   wait2,
//   wait3,
//   msg_1,
//   msg_2,
//   msg_3,
//   msg_4
// };
// const int n_actions = vertical_shake+1;
// const int n_states = msg_4+1;
// int target_hist[n_states];
// String target_map[n_actions] = {"neutral", "clockwise", "counterclockwise", "horizontal_shake", "vertical_shake"};
// String state_map[n_states] = {"wait1", "wait2", "wait3", "omw", "omw 5 min", "omw 15 min", "omw 30 min"};


// int map_prediction(String prediction) {
//   int target;
//   if(prediction == "neutral")
//     target = neutral;
//   else if(prediction == "clockwise")
//     target = clockwise;
//   else if(prediction == "counterclockwise")
//     target = counterclockwise;
//   else if(prediction == "horizontal_shake") // this isnt a typo, I accidentially switched the lables while training
//     target = vertical_shake;
//   else if(prediction == "vertical_shake")
//     target = horizontal_shake;
//   else
//     target = error;

//   return target;
// }

// int state = wait1;
// int s0 = -1, s1 = -1, s2 = -1;

// int detect_gesture(int target) {
//   buffer[buf_idx%N] = target;

//   if(buf_idx >= N) {
//     // use the most frequently detected target in
//     // a window of N elements
//     memset(target_hist, 0, sizeof(int)*n_actions);
//     for(int i=0; i<N; i++)
//       target_hist[buffer[(buf_idx-i)%N]]++;
//     int max_state_count = -1;
//     prev_target = curr_target;
//     for(int i=0; i<n_actions; i++) {
//       if(target_hist[i] > max_state_count) {
//         max_state_count = target_hist[i];
//         curr_target = i;
//       }
//     }
//     Serial.println(target_map[curr_target]);

//     // All state transition changes require neutral-[some non-neutral state]-neutral
//     if(state == msg_1 || state == msg_2 || state == msg_3 || state == msg_4)
//       state = wait1;
//     if(curr_target != prev_target) {
//       s0 = s1;
//       s1 = prev_target;
//       s2 = curr_target;
//       Serial.print(s0);
//       Serial.print(s1);
//       Serial.println(s2);

//       if(state == wait1) {
//         if(s0 == neutral && s1 == clockwise && s2 == neutral)
//           state = wait2;
//       }
//       else if(state == wait2) {
//         if(s0 == neutral && s1 == clockwise && s2 == neutral)
//           state = wait3;
//         else if(s2 != neutral && s2 != clockwise) // TODO havent thought this out properly
//           state = wait1;
//       }
//       else if(state == wait3) {
//         if(s0 == neutral && s1 != neutral && s2 == neutral) {
//           if(s1 == clockwise) state = msg_1;
//           else if(s1 == counterclockwise) state = msg_2;
//           else if(s1 == vertical_shake) state = msg_3;
//           else if(s1 == horizontal_shake) state = msg_4;
//         }
//       }
//     }
//     Serial.println(state_map[state]);
//   }

//   buf_idx++;
  
//   return state;
// }

void loop() {
  float ax, ay, az, gx, gy, gz;
  webSocket.loop();

  static unsigned long lastSendTime = 0;
  unsigned long currentMillis = millis();

  //data send every ,1 secs
  
    // await for data
    if (!IMU.accelerationAvailable() || !IMU.gyroscopeAvailable())
      return;
      
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    // perform feature extraction
    float features[] = {ax, ay, az, gx, gy, gz};
      
    if (!pipeline.transform(features))
      return;
      
    // perform classification
    String prediction = forest.predictLabel(pipeline.X);
    int target = map_prediction(prediction);
    if(target < 0) {
      Serial.print("Error\n");
      while(1);
    }
    int state = detect_gesture(target);
    // if(state == msg_1 || state == msg_2 || state == msg_3 || state == msg_4) {
    if(state_is_message(state)) {
      // TODO: add web socket link here
      // state_map[state] returns is an array of strings that gives the message to be sent like a hash table
      Serial.print("------ Message: ");
      Serial.print(state_map[state]);
      webSocket.sendTXT(String(state_map[state]));
      Serial.println("-------");
    }

    Serial.print("Predicted gesture: ");
    Serial.print(prediction);
    Serial.print(" (DSP: ");
    Serial.print(pipeline.latencyInMicros());
    Serial.print(" micros, Classifier: ");
    Serial.print(forest.latencyInMicros());
    Serial.println(" micros)");
}

void webSocketEvent(const WStype_t& type, uint8_t* payload, const size_t& length) {
  switch (type) {
    case WStype_DISCONNECTED:
      if (alreadyConnected) {
        Serial.println("[WSc] Disconnected!");
        alreadyConnected = false;
      }
      break;

    case WStype_CONNECTED:
      {
        alreadyConnected = true;
        Serial.print("[WSc] Connected to url: ");
        Serial.println((char*)payload);
        // send a message to server when Connected
        webSocket.sendTXT("Connected");
      }
      break;

    case WStype_TEXT:
      // Log the received text message
      Serial.print("[WSc] Received text: ");
      Serial.println((char *) payload);
      //Should be NONE
      break;

    case WStype_BIN:
      // Log binary messages (if needed)
      Serial.print("[WSc] Received binary length: ");
      Serial.println(length);
      // Should be NONE
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


void printWifiStatus() {
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
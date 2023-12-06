// file IMUClassify.ino

#include <Arduino_LSM6DS3.h>
#include "Pipeline.h"
#include "Classifier.h"

int buf_idx = 0;
const int N = 6;
int buffer[N];
int curr_target = -1;
int prev_target = -1;
int prev_prev_target = -1;

void setup() {
  Serial.begin(115200);
  Serial.println("Started");

  while (!IMU.begin()) 
    Serial.println("Failed to initialize IMU!");

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

enum targets {
  error = -1,
  neutral,
  clockwise,
  counterclockwise,
  horizontal_shake,
  vertical_shake
};

enum states {
  wait1,
  wait2,
  wait3,
  omw,
  omw_5,
  omw_15,
  omw_30
};
const int n_targets = vertical_shake+1;
const int n_states = omw_30+1;
int target_hist[n_states];
String target_map[n_targets] = {"neutral", "clockwise", "counterclockwise", "horizontal_shake", "vertical_shake"};
String state_map[n_states] = {"wait1", "wait2", "wait3", "omw", "omw_5", "omw_15", "omw_30"};


int map_prediction(String prediction) {
  int target;
  if(prediction == "neutral")
    target = neutral;
  else if(prediction == "clockwise")
    target = clockwise;
  else if(prediction == "counterclockwise")
    target = counterclockwise;
  else if(prediction == "horizontal_shake") // this isnt a typo, I accidentially switched the lables while training
    target = vertical_shake;
  else if(prediction == "vertical_shake")
    target = horizontal_shake;
  else
    target = error;

  return target;
}

int state = wait1;
int s0 = -1, s1 = -1, s2 = -1;

int detect_gesture(int target) {
  buffer[buf_idx%N] = target;

  if(buf_idx >= N) {
    // use the most frequently detected target in
    // a window of N elements
    memset(target_hist, 0, sizeof(int)*n_targets);
    for(int i=0; i<N; i++)
      target_hist[buffer[(buf_idx-i)%N]]++;
    int max_state_count = -1;
    prev_target = curr_target;
    for(int i=0; i<n_targets; i++) {
      if(target_hist[i] > max_state_count) {
        max_state_count = target_hist[i];
        curr_target = i;
      }
    }
    Serial.println(target_map[curr_target]);

    // All state transition changes require neutral-[some non-neutral state]-neutral
    if(state == omw || state == omw_5 || state == omw_15 || state == omw_30)
      state = wait1;
    if(curr_target != prev_target) {
      s0 = s1;
      s1 = prev_target;
      s2 = curr_target;
      Serial.print(s0);
      Serial.print(s1);
      Serial.println(s2);

      if(state == wait1) {
        if(s0 == neutral && s1 == clockwise && s2 == neutral)
          state = wait2;
      }
      else if(state == wait2) {
        if(s0 == neutral && s1 == clockwise && s2 == neutral)
          state = wait3;
        else if(s2 != neutral && s2 != clockwise) // TODO havent thought this out properly
          state = wait1;
      }
      else if(state == wait3) {
        if(s0 == neutral && s1 != neutral && s2 == neutral) {
          if(s1 == clockwise) state = omw;
          else if(s1 == counterclockwise) state = omw_5;
          else if(s1 == vertical_shake) state = omw_15;
          else if(s1 == horizontal_shake) state = omw_30;
        }
      }
    }
    Serial.println(state_map[state]);
  }

  buf_idx++;
  
  return state;
}

void loop() {
  float ax, ay, az, gx, gy, gz;
  
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
  if(state == omw || state == omw_5 || state == omw_15 || state == omw_30) {
    Serial.print("------ Message: ");
    Serial.print(state_map[state]);
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
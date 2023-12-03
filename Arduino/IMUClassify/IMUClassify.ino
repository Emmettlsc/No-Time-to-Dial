// file IMUClassify.ino

#include <Arduino_LSM6DS3.h>
#include "Pipeline.h"
#include "Classifier.h"


void setup() {
  Serial.begin(115200);
  Serial.println("Started");

  while (!IMU.begin()) 
    Serial.println("Failed to initialize IMU!");

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
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
  Serial.print("Predicted gesture: ");
  Serial.print(forest.predictLabel(pipeline.X));
  Serial.print(" (DSP: ");
  Serial.print(pipeline.latencyInMicros());
  Serial.print(" micros, Classifier: ");
  Serial.print(forest.latencyInMicros());
  Serial.println(" micros)");
}
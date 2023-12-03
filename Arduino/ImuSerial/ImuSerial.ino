#include <Arduino_LSM6DS3.h>


void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println("Hz");
}

void loop() {
  float ax, ay, az, gx, gy, gz;
  
  if (!IMU.accelerationAvailable() || !IMU.gyroscopeAvailable())
    return;
    
  IMU.readAcceleration(ax, ay, az);
  IMU.readGyroscope(gx, gy, gz);

  Serial.print("IMU: ");
  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.print(az);
  Serial.print(",");
  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.print(gz);
  Serial.print("\n");
}
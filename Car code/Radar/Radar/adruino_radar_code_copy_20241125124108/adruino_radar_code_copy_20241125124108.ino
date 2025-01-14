#include <Servo.h>  // No longer needed since servo is not used

int dis;  // Variable to store distance reading
const int obstacleThreshold = 10; // Distance threshold for obstacle detection (in cm)

void setup() {
  pinMode(2, OUTPUT);  // Define trigger pin for ultrasonic sensor
  pinMode(3, INPUT);   // Define echo pin for ultrasonic sensor
  Serial.begin(9600);  // Start serial communication for Bluetooth
}

void loop() {
  dis = distance();  // Measure distance
  
  // Check if obstacle is detected
  if (dis <= obstacleThreshold) {
    sendStopSignal();  // Send stop signal if obstacle is detected
  }

  sendData(dis);  // Send distance via Bluetooth
  delay(50);  // Adjust the delay as needed
}

// Measure distance using ultrasonic sensor
int distance() {
  digitalWrite(2, LOW);
  delayMicroseconds(4);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);

  int t = pulseIn(3, HIGH);
  int cm = t / 29 / 2;  // Convert time to distance in cm
  return cm;  // Return the distance
}

// Send data (distance only) via Bluetooth
void sendData(int distance) {
  Serial.print("0,");  // Angle is fixed at 0 (facing forward)
  Serial.print(distance);  // Send distance via Bluetooth
  Serial.println(".");   // End of data
}

// Send a "STOP" signal to the Processing application
void sendStopSignal() {
  Serial.println("STOP");  // Send STOP signal via Bluetooth
}

#include <PS2X_lib.h>
#include <NewPing.h>

PS2X ps2x;

// Ultrasonic sensor setup
#define TRIG_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Initialize ultrasonic sensor

int error = 0;
byte type = 0;
byte vibrate = 0;
bool joystickEnabled = false;
bool obstacleAvoidanceEnabled = true; // Variable to toggle obstacle avoidance
int speed = 255;
const int ledPin = 13;

// Motor Driver 1 (Front Wheels) pins
const int motor1pin1 = 4;
const int motor1pin2 = 5;
const int motor2pin1 = 6;
const int motor2pin2 = 7;
const int ENA = 8;
const int ENB = 9;

// Motor Driver 2 (Rear Wheels) pins
const int motor3pin1 = 10;
const int motor3pin2 = 11;
const int motor4pin1 = 12;
const int motor4pin2 = 13;
const int ENA2 = 14;
const int ENB2 = 15;

void setup() {
    Serial.begin(57600);

    // Configure all motor pins
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(motor3pin1, OUTPUT);
    pinMode(motor3pin2, OUTPUT);
    pinMode(motor4pin1, OUTPUT);
    pinMode(motor4pin2, OUTPUT);
    pinMode(ENA2, OUTPUT);
    pinMode(ENB2, OUTPUT);

    stop();

    error = ps2x.config_gamepad(A5, A4, A3, A2, true, true);

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    if (error == 0) {
        Serial.println("Controller configured successfully");
    } else {
        Serial.print("Error configuring controller: ");
        Serial.println(error);
    }

    type = ps2x.readType();
    switch (type) {
        case 0: Serial.println("Unknown Controller type"); break;
        case 1: Serial.println("DualShock Controller Found"); break;
        case 2: Serial.println("GuitarHero Controller Found"); break;
    }
}

// Function to read distance from ultrasonic sensor
int getDistance() {
    return sonar.ping_cm();
}

// Unified movement functions for 4 wheels
void forward(int speed) {
    // Check for obstacle
    if (obstacleAvoidanceEnabled && getDistance() <= 10) {
        stop();
        return;
    }

    // Move forward
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, HIGH);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}

// Define other movement functions similarly (back, left, right, etc.)

void stop() {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    analogWrite(ENA2, 0);
    analogWrite(ENB2, 0);
}

void loop() {
    if (error) return;

    ps2x.read_gamepad(false, vibrate);

    // Toggle obstacle avoidance with a button (e.g., PSB_R2)
    if (ps2x.Button(PSB_R2)) {
        obstacleAvoidanceEnabled = !obstacleAvoidanceEnabled;
        Serial.print("Obstacle Avoidance: ");
        Serial.println(obstacleAvoidanceEnabled ? "Enabled" : "Disabled");
    }

    // Joystick mode toggle with R1
    if (ps2x.Button(PSB_R1)) {
        joystickEnabled = true;
        digitalWrite(ledPin, HIGH);
        Serial.println("Enabled");

        if (ps2x.Button(PSB_PAD_UP)) {
            forward(speed);
        } else if (ps2x.Button(PSB_PAD_DOWN)) {
            back(speed);
        } else if (ps2x.Button(PSB_PAD_LEFT)) {
            left(speed);
        } else if (ps2x.Button(PSB_PAD_RIGHT)) {
            right(speed);
        } else {
            joystickEnabled = false;
            Serial.println("Disabled");
            digitalWrite(ledPin, LOW);
            stop();
        }
    }

    delay(50);
}

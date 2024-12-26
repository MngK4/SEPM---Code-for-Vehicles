#include <PS2X_lib.h>

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;
bool joystickEnabled = false;
int speed = 255;

const int ledPin = 13;

// Motor Driver 1 (Front Wheels) pins
const int motor1pin1 = 2;  // Front-left IN1 red-OUT1
const int motor1pin2 = 3;  // Front-left IN2 black-OUT2
const int motor2pin1 = 4;  // Front-right IN3 red-OUT3
const int motor2pin2 = 5;  // Front-right IN4 black-OUT4
const int ENA = 6;         // Front enable pin
const int ENB = 7;         // Front enable pin

// Motor Driver 2 (Rear Wheels) pins
const int motor3pin1 = 8;  // Rear-left IN1  red-OUT1
const int motor3pin2 = 9;  // Rear-left IN2  black-OUT2
const int motor4pin1 = 10; // Rear-right IN3 red-OUT3
const int motor4pin2 = 11; // Rear-right IN4 black-OUT4
const int ENA2 = 12;       // Rear enable pin
const int ENB2 = 13;       // Rear enable pin

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

    // Initialize motor states
    stop();

    // Configure PS2 controller
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

// Unified movement functions for 4 wheels
void forward(int speed) {
    // Front wheels
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

    // Rear wheels
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, HIGH);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}

void back(int speed) {
    // Front wheels
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);

    // Rear wheels
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);
    digitalWrite(motor4pin1, HIGH);
    digitalWrite(motor4pin2, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}

void left(int speed) {
    // right wheels

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    digitalWrite(motor4pin1, LOW);
    digitalWrite(motor4pin2, HIGH);

    // left wheels
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);

    


    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}


void right(int speed) {
    // left wheels
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);
 

    // right wheels
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    digitalWrite(motor4pin1, HIGH);
    digitalWrite(motor4pin2, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}





// NEW
void sidewayRight(int speed) {
  // Front-left 
    digitalWrite(motor1pin1, HIGH);  // FL forward
    digitalWrite(motor1pin2, LOW);

  // Rear left
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);

  // Front-right
    digitalWrite(motor2pin1, LOW); // FR forward
    digitalWrite(motor2pin2, HIGH);

  // Rear-right
    digitalWrite(motor4pin1, LOW); // FR forward
    digitalWrite(motor4pin2, HIGH);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed); 
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}




//NEW SIDEWAYLEFT

void sidewayLeft(int speed) {
   // Front left
    digitalWrite(motor1pin1, LOW);  // FL forward
    digitalWrite(motor1pin2, HIGH);

  // Rear left
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);

  // Front-right
    digitalWrite(motor2pin1, HIGH); // FR forward
    digitalWrite(motor2pin2, LOW);

  // Rear-right
    digitalWrite(motor4pin1, HIGH); // FR forward
    digitalWrite(motor4pin2, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);

}




void diagonalUpLeft(int speed) {
   // Front-left
    digitalWrite(motor1pin1, HIGH);  // FL forward
    digitalWrite(motor1pin2, LOW);

  // Rear right
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, LOW);

  // Front-right
    digitalWrite(motor2pin1, LOW); // FR forward
    digitalWrite(motor2pin2, LOW);

  // Rear-left
    digitalWrite(motor4pin1, LOW); // FR forward
    digitalWrite(motor4pin2, HIGH);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}


void diagonalUpRight(int speed) {
   // Front-left
    digitalWrite(motor1pin1, LOW);  // FL forward
    digitalWrite(motor1pin2, LOW);

    // Front-right
    digitalWrite(motor2pin1, HIGH); // FR forward
    digitalWrite(motor2pin2, LOW);

  // Rear right
    digitalWrite(motor3pin1, HIGH);
    digitalWrite(motor3pin2, LOW);



  // Rear-left
    digitalWrite(motor4pin1, LOW); // FR forward
    digitalWrite(motor4pin2, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}





void diagonalDownLeft(int speed) {
   // Front-left
    digitalWrite(motor1pin1, LOW);  // FL forward
    digitalWrite(motor1pin2, HIGH);

  // Rear right
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, LOW);

  // Front-right
    digitalWrite(motor2pin1, LOW); // FR forward
    digitalWrite(motor2pin2, LOW);

  // Rear-left
    digitalWrite(motor4pin1, HIGH); // FR forward
    digitalWrite(motor4pin2, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}


void diagonalDownRight(int speed) {
   // Front-left
    digitalWrite(motor1pin1, LOW);  // FL forward
    digitalWrite(motor1pin2, LOW);

    // Front-right
    digitalWrite(motor2pin1, LOW); // FR forward
    digitalWrite(motor2pin2, HIGH);

  // Rear right
    digitalWrite(motor3pin1, LOW);
    digitalWrite(motor3pin2, HIGH);



  // Rear-left
    digitalWrite(motor4pin1, LOW); // FR forward
    digitalWrite(motor4pin2, LOW);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENA2, speed);
    analogWrite(ENB2, speed);
}


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
        } else if (ps2x.Button(PSB_RED)) {
            sidewayRight(speed);
        } else if (ps2x.Button(PSB_PINK)) {
            sidewayLeft(speed);
        } else if (ps2x.Button(PSB_GREEN)) {
            diagonalUpLeft(speed);
        } else if (ps2x.Button(PSB_BLUE)) {
            diagonalUpRight(speed);
        } else {
          joystickEnabled = false;
          Serial.println("Disabled");
          digitalWrite(ledPin, LOW);
          stop();
        }
    }

     // Joystick mode toggle with R2
    if (ps2x.Button(PSB_L1)) {
        joystickEnabled = true;
        digitalWrite(ledPin, HIGH);
        Serial.println("Enabled");

   
        if (ps2x.Button(PSB_GREEN)) {
            diagonalDownLeft(speed);
        } else if (ps2x.Button(PSB_BLUE)) {
            diagonalDownRight(speed);
        } else {
          joystickEnabled = false;
          Serial.println("Disabled");
          digitalWrite(ledPin, LOW);
          stop();
        }
    }

    delay(50);
}

import processing.serial.*;  // Import the serial library for Bluetooth communication
import java.util.*;  // This is generally included by default, but in case you need additional utilities

PFont f;  // Font object for text
int Distance;
String distance = "";
String data;
int index1 = 0;
float pixsDistance;
boolean obstacleDetected = false;  // Flag to track if the obstacle is within 10 cm

int simulatedAngle = 0;  // Simulated angle for sweeping radar
boolean sweepDirection = true;  // Direction of the radar sweep (true = right, false = left)

Serial myport;  // Create serial object to communicate with Arduino

void setup() {
  size(1250, 700);  // Screen size
  smooth();
  
  // Set font for displaying text
  f = createFont("David Bold", 30); 
  textFont(f);

  // List available serial ports and select the correct one for Bluetooth
  String[] portList = Serial.list();  // Get the list of serial ports
  println("Available Serial Ports:");
  for (int i = 0; i < portList.length; i++) {
    println(i + ": " + portList[i]);
  }

   //Adjust the index according to the correct port
  String portName = portList[6];  // Select the 8th port (adjust if needed)
  println("Selected Port: " + portName);

  myport = new Serial(this, portName, 9600);  // Initialize the serial communication
  myport.bufferUntil('.');  // Set buffer to stop at a period (.)
}

void draw() {
  background(0, 10);  // Transparent background for fading effect
  fill(98, 245, 31); 
  greenmesh();  // Draw the green mesh for radar area
  radararea();  // Draw the radar area (half-circle)
  
  if (obstacleDetected) {
    fill(255, 0, 0);  // Red color for stop message
    text("STOP! Obstacle Detected", 500, 30);  // Display STOP message
  }

  words();  // Display angle and distance on the screen
  greenLine();  // Draw the green line for current simulated angle
  redline();  // Draw the red line based on distance
  updateSimulatedAngle();  // Update the sweeping angle
}

void serialEvent(Serial myport) { 
  data = myport.readStringUntil('.');  // Read data until period is encountered
  if (data != null) {
    data = data.trim();  // Clean up any extra spaces

    index1 = data.indexOf(",");  // Find comma separating angle and distance
    if (index1 != -1) {
      distance = data.substring(index1 + 1);  // Extract distance

      // Convert the String variable into an integer
      Distance = int(distance);

      // Check if obstacle is within 10 cm
      if (Distance <= 10) {
        obstacleDetected = true;  // Set flag if obstacle is detected
      } else {
        obstacleDetected = false;  // Clear flag if obstacle is not detected
      }
    }
  }
}

// Simulate the radar sweep by incrementing/decrementing the angle
void updateSimulatedAngle() {
  if (sweepDirection) {
    simulatedAngle += 2;  // Sweep to the right
    if (simulatedAngle >= 180) sweepDirection = false;  // Reverse direction
  } else {
    simulatedAngle -= 2;  // Sweep to the left
    if (simulatedAngle <= 0) sweepDirection = true;  // Reverse direction
  }
}

// Draw the radar area with half-circle arcs and lines at specific angles
void radararea() {
  pushMatrix();
  translate(625, 680);  // Move to the center of the screen
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);

  // Draw half circles for different distance ranges
  arc(0, 0, 1150, 1150, PI, TWO_PI);
  arc(0, 0, 850, 850, PI, TWO_PI);
  arc(0, 0, 550, 550, PI, TWO_PI);
  arc(0, 0, 250, 250, PI, TWO_PI);

  // Draw lines at different angles (predefined, not moving)
  for (int i = 0; i <= 180; i += 30) {
    line(0, 0, -600 * cos(radians(i)), -600 * sin(radians(i)));
  }

  popMatrix();
}

// Draw the green mesh (grid lines)
void greenmesh() {
  stroke(98, 245, 31);
  strokeWeight(0.1);
  for (int x = 0; x <= 700; x += 5) {
    line(0, x, width, x);
  }
  for (int y = 0; y <= 1250; y += 5) {
    line(y, 0, y, height);
  }
}

// Display angle and distance values on the screen
void words() {
  fill(98, 245, 31);
  text("180'", 10, 670);
  fill(98, 245, 31);
  text("0'", 1210, 670);
  fill(98, 245, 31);
  text("30'", 1160, 380);
  fill(98, 245, 31);
  text("60'", 940, 160);
  fill(98, 245, 31);
  text("90'", 615, 70);
  fill(98, 245, 31);
  text("120'", 310, 150);
  fill(98, 245, 31);
  text("150'", 80, 370);
  fill(255);
  text("Radar system", 20, 30);
  fill(255);
  text("Angle -- " + simulatedAngle + " '", 20, 60);
  fill(255);
  text("Distance -- " + Distance + " cm", 20, 90);
}

// Draw the green line based on the current simulated angle
void greenLine() {
  pushMatrix();
  strokeWeight(7);
  stroke(30, 250, 60);  // Green color
  translate(625, 680);  // Move to the center of the screen
  line(0, 0, 600 * cos(radians(simulatedAngle)), -600 * sin(radians(simulatedAngle)));  // Draw the line based on the current simulated angle
  popMatrix();
}

// Draw the red line based on the distance (distance will control the line length)
void redline() {
  pushMatrix();
  translate(625, 680);  // Move to the center of the screen
  strokeWeight(7);
  stroke(255, 10, 10);  // Red color
  pixsDistance = Distance * 22.5;  // Scale the distance for visualization

  // Draw the red line at the given angle and distance
  if (Distance < 40) {  // Limiting the range to 40 cm for visualization
    line(pixsDistance * cos(radians(simulatedAngle)), -pixsDistance * sin(radians(simulatedAngle)), 600 * cos(radians(simulatedAngle)), -600 * sin(radians(simulatedAngle)));
  }
  popMatrix();
}

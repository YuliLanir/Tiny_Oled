#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "image_test.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

#define MOTION_PIN 18

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Koala dimensions (based on your 46-byte array)
const int KOALA_WIDTH = 16;
const int KOALA_HEIGHT = 23;

// Movement variables
int posX = 0;      // Current X position
int posY = 0;      // Current Y position
int speedX = 2;    // How many pixels to move horizontally per frame
int speedY = 1;    // How many pixels to move vertically per frame

void setup() {
  Serial.begin(115200);

  pinMode(MOTION_PIN, INPUT); // Set the PIR pin as an input

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
}

void koala_motion(){
  // 2. Draw the koala at the current position
  display.drawBitmap(posX, posY, koala, KOALA_WIDTH, KOALA_HEIGHT, WHITE);

  // 3. Show the frame
  display.display(); 

  // 4. Update the position for the next frame
  posX += speedX;
  posY += speedY;

  // 5. Boundary Detection: Bounce off the walls
  if (posX <= 0 || posX >= (SCREEN_WIDTH - KOALA_WIDTH)) {
    speedX = -speedX; // Reverse horizontal direction
  }
  
  if (posY <= 0 || posY >= (SCREEN_HEIGHT - KOALA_HEIGHT)) {
    speedY = -speedY; // Reverse vertical direction
  }

  // Small delay to control the speed of animation
  delay(10); 
}

void loop() {
  

  display.clearDisplay();
  
  int motionState = digitalRead(MOTION_PIN); // Read the pin state

  delay(1000);
  Serial.println(motionState);

  if (motionState == HIGH) {
    Serial.println("MOTION DETECTED!");
  } else {
    koala_motion();
  }

  
}
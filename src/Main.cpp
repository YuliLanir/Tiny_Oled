#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>
#include "Entities.h"
#include "Logic.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Preferences prefs;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);
  
  // Load High Score from Flash
  prefs.begin("game", false);
  highScore = prefs.getInt("hscore", 0);
  
  resetGame();
}

void loop() {
  display.clearDisplay();
  
  handleInput();
  updateObjects();
  checkCollisions();
  drawUI();
  
  display.display();
  delay(10); // Maintain frame rate
}


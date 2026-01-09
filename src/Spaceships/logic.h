#include "Entities.h"

void handleInput() {
bool left = !digitalRead(LEFT_BTN);
bool right = !digitalRead(RIGHT_BTN);

  if (left && !right) {
    ship.x -= 2; // move left
    if (ship.x < 0) ship.x = 0; // boundary check
  } else if (right && !left) {
    ship.x += 2; // move right
    if (ship.x + ship.width > SCREEN_WIDTH) ship.x = SCREEN_WIDTH - ship.width; // boundary check
  }
}

// Check for collisions between ship and falling objects
void checkCollisions(){
  // Implement collision detection between ship and falling objects
  for (int i = 0; i < Objects.size(); i++) {
    GameObject &obj = Objects[i];
    if (obj.type == ASTEROID || obj.type == FUEL_TANK) {
      // Simple AABB collision detection
      if (ship.x < obj.x + obj.width &&
          ship.x + ship.width > obj.x &&
          ship.y < obj.y + obj.height &&
          ship.y + ship.height > obj.y) {
            
        // Collision detected
        if (obj.type == ASTEROID) {
          livesObj.infoValue--;
          // Remove asteroid
          Objects.erase(Objects.begin() + i);

        } else if (obj.type == FUEL_TANK) {
          fuelObj.infoValue = min(fuelObj.infoValue + 1, 5); // max fuel is 5
          // Remove fuel tank
          Objects.erase(Objects.begin() + i);
        }
      }
    }
  }

}


void draw_numbers(int x, int y, int number) {
  // Draw each digit of the number
  String numStr = String(number);
  for (int i = 0; i < numStr.length(); i++) {
    char digit = numStr.charAt(i);
    const unsigned char* bitmap = nullptr;
    int width = 0;
    switch (digit) {
      case '0': bitmap = epd_bitmap_number_0; width = number_0_width; break;
      case '1': bitmap = epd_bitmap_number_1; width = number_1_width; break;
      case '2': bitmap = epd_bitmap_number_2; width = number_2_width; break;
      case '3': bitmap = epd_bitmap_number_3; width = number_3_width; break;
      case '4': bitmap = epd_bitmap_number_4; width = number_4_width; break;
      case '5': bitmap = epd_bitmap_number_5; width = number_5_width; break;
      case '6': bitmap = epd_bitmap_number_6; width = number_6_width; break;
      case '7': bitmap = epd_bitmap_number_7; width = number_7_width; break;
      case '8': bitmap = epd_bitmap_number_8; width = number_8_width; break;
      case '9': bitmap = epd_bitmap_number_9; width = number_9_width; break;
    }
    if (bitmap) {
      display.drawBitmap(x, y, bitmap, width, number_0_height, WHITE);
      x += width + 1; // Move x for next digit
    }
  }
}

void updateStats(Adafruit_SSD1306 &display){
  // Update score
  draw_numbers(scoreObj.x + 5, scoreObj.y, scoreObj.infoValue);
  // Update high score
  draw_numbers(highScoreObj.x + 5, highScoreObj.y, highScoreObj.infoValue);

  // Draw lives
  for (int i = 0; i < livesObj.infoValue; i++) {
    display.drawBitmap(SCREEN_WIDTH - (i + 1) * (heart_width + 2), 0, epd_bitmap_heart, heart_width, heart_height, WHITE);
  }

  // Draw fuel
  for (int i = 0; i < fuelObj.infoValue; i++) {
    display.fillRect(0 + i * 6, SCREEN_HEIGHT - 8, 5, 5, WHITE);
  }
}


// int updateHighScore() {
//   if (scoreObj.infoValue > highScore) {
//     highScore = scoreObj.infoValue ;
//     // Save to ESP32 Flash memory permanently
//     prefs.putInt("hscore", highScore); 
//   }
// }


void drawUI(Adafruit_SSD1306 &display) {
  display.clearDisplay();
  // Draw ship
  display.drawBitmap(ship.x, ship.y, ship.sprite, ship.width, ship.height, WHITE);

  // Draw falling objects
  for (const auto &obj : Objects) {
    display.drawBitmap(obj.x, obj.y, obj.sprite, obj.width, obj.height, WHITE);
  }

  updateStats(display);
  
}
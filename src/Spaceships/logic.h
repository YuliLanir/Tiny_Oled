void handleInput() {
  bool left = !digitalRead(LEFT_BTN);
  bool right = !digitalRead(RIGHT_BTN);

  if (left && right) {
    shootBullet(); // Both buttons = Shoot
  } else if (left && ship.x > 0) {
    ship.x -= 2;
  } else if (right && ship.x < 120) {
    ship.x += 2;
  }
}

void checkCollisions() {
  // Logic for Bullet vs Asteroid
  for(int i=0; i<5; i++) {
    if(bullets[i].active) {
      for(int j=0; j<5; j++) {
        if(asteroids[j].active && dist(bullets[i], asteroids[j]) < 5) {
          asteroids[j].active = false;
          bullets[i].active = false;
          score++;
          updateHighScore();
        }
      }
    }
  }
}

void updateHighScore() {
  if (score > highScore) {
    highScore = score;
    // Save to ESP32 Flash memory permanently
    prefs.putInt("hscore", highScore); 
  }
}
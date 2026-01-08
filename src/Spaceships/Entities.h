#define LEFT_BTN 14
#define RIGHT_BTN 12

struct GameObject {
  float x, y;
  bool active;
};

GameObject ship = {64, 55, true};
GameObject bullets[5];     // Max 5 bullets on screen
GameObject asteroids[5];   // Max 5 asteroids on screen
GameObject fuelTank = {0, 0, false};

int score = 0;
int highScore = 0;
int lives = 3;
int fuel = 5; // 5 lines/bars
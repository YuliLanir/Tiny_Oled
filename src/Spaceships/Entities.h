#ifndef SPACESHIPS_ENTITIES_H
#define SPACESHIPS_ENTITIES_H

#include <vector>
#include "Config.h"
#include "App_Globals.h"

#define MAX_SPAWN_OBJECTS 8
#define MIN_ACTIVE_OBJECTS 3

// Define entity types /////////////////////

using bitmap = const unsigned char*;

enum EntityType {
  SHIP,
  BULLET,
  ASTEROID,
  FUEL_TANK,
}; 

enum InfoType {
  SCORE,
  HIGH_SCORE,
  LIVES,
  FUEL_BARS
};

struct GameObject {
  int x, y; // coordinates
  int width, height; // size
  int speed = 0;
  EntityType type = SHIP;
  bitmap sprite;

  GameObject(int x = 0, int y = 0, int width = 0, int height = 0, int speed = 0, EntityType type = SHIP, bitmap sprite = nullptr)
    : x(x), y(y), width(width), height(height), speed(speed), type(type), sprite(sprite) {}
};

struct GameStat{
  int x, y; // coordinates
  int width, height; // size
  int infoValue = 0;
  bitmap sprite;

  GameStat(int x = 0, int y = 0, int width = 0, int height = 0, int infoValue = 0, bitmap sprite = nullptr)
    : x(x), y(y), width(width), height(height), infoValue(infoValue), sprite(sprite) {}
};
 //////////////////////////////////////////


// Craete all game objects


// Game stats
GameStat scoreObj(0, 0, score_width, score_height, 0, epd_bitmap_score);
GameStat highScoreObj(0, 0, high_score_width, high_score_height, 0, epd_bitmap_high_score);
GameStat fuelObj(0, 0, fuel_width, fuel_height, 0, epd_bitmap_fuel );
GameStat livesObj(0, 0, 10, 7, 0, epd_bitmap_heart);

// Dynamic list of objects
std::vector<GameObject> Objects;

// The player's ship
GameObject ship(0, 0, rocketship_width, rocketship_height, 0, SHIP, epd_bitmap_rocketship);


// Initializes game state and places the rocket centered at the lower screen edge.

void setupGame() {
  // Initialize ship position
  // center ship horizontally and place near bottom
  ship.x = (SCREEN_WIDTH / 2) - (int)(ship.width / 2);
  ship.y = SCREEN_HEIGHT - (int)ship.height - 1;

  // Initialize game variables
  ObjSpeed = DEFAULT_OBJ_SPEED; // reset asteroid speed
  ShipSpeed = DEFAULT_SHIP_SPEED; // reset ship speed  
  ship.speed = ShipSpeed;

  // Reset score, lives, fuel
  scoreObj.infoValue = DEFAULT_SCORE;
  livesObj.infoValue = DEFAULT_LIVES;
  fuelObj.infoValue = DEFAULT_FUEL; 
}

// Called each frame: spawn new objects off-screen (y > 64) with NEGATIVE speed and update positions.
void updateObjects() {

  // Move existing objects  
  for (int i = 0; i < MAX_SPAWN_OBJECTS; i++) {
    if (Objects[i].speed != 0) { // active object
      Objects[i].y += Objects[i].speed;
    }
    if (Objects[i].y > SCREEN_HEIGHT) {
      Objects.erase(Objects.begin() + i); // Actually deletes the object
    }
  }

  // Spawn new objects if object count is below minimum
  if (Objects.size() < MIN_ACTIVE_OBJECTS) {
    // genretae either fuel tank or asteroid - 1/4 fuel tank, 3/4 asteroid
    GameObject NewObject;
    NewObject.type = (random(0, 3) == 0) ? FUEL_TANK : ASTEROID;
    NewObject.width = 10; // example width
    NewObject.height = 10; // example height
    NewObject.speed = ObjSpeed;
    NewObject.x = random(0, SCREEN_WIDTH - NewObject.width);
    NewObject.y = SCREEN_HEIGHT; // start just off-screen

    //if asteroid, randomly select what kind of asteroid 1 2 or 3
    if (NewObject.type  == ASTEROID) {
      // assign sprite based on random selection
      int asteroidType = random(1, 4);
      switch (asteroidType) {
        case 1:
          NewObject.sprite = epd_bitmap_asteroid1;
          NewObject.height = asteroid1_height;
          NewObject.width = asteroid1_width;
          break;
        case 2:
          NewObject.sprite = epd_bitmap_asteroid2;
          NewObject.height = asteroid2_height;
          NewObject.width = asteroid2_width;  
          break;
        case 3:
          NewObject.sprite = epd_bitmap_asteroid3;
          NewObject.height = asteroid3_height;
          NewObject.width = asteroid3_width;
          break;
      }

    } else if (NewObject.type == FUEL_TANK) {
        NewObject.sprite = epd_bitmap_fuel_tank;
        NewObject.height = fuel_tank_height;
        NewObject.width = fuel_tank_width;  
    }
  
  Objects.push_back(NewObject);
  }

  //every 10 calls increase speed of asteroids and ship
  static int frameCounter = 0;
  frameCounter++;
  if (frameCounter >= 10) {
    ObjSpeed++;
    ship.speed++;
    frameCounter = 0;
  }
}







#endif // SPACESHIPS_ENTITIES_H
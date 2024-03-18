#include "GameInitialization.h"

//Constants
const int TILE_LENGTH = 100; 
const int playerMoveSpeed = 10; 
const int maxTreesInARow = 2; 
const int maxSticksInARow = 5;
const int minSticksInARow = 2;
const int maxCoinsInARow = 2;
const int FPS = 60;
const int delay = 1000 / FPS;
const int cameraBaseSpeed = 1; 
int trainMoveSpeed = 18; 

//Variables
int startLoop, endLoop;
int cameraSpeed = cameraBaseSpeed;
int gameEvent;
int rows, columns;
int maxScore = 0, score = 0, topScore = 0, coins = 0;
char chars[10] ; //Used in updateScore();
bool eagleIntersection = false;

deque<Object> objects ;




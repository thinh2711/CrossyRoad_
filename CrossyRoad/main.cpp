#include "Genio.h"
#include <cstdlib>
#include <ctime>
#include <deque>

using namespace std;

enum TileType { GRASS, WATER, ROAD, RAIL, TREE };
enum ObjectType { PLAYER, CAR, TRAIN, STICK, LAMP, EAGLE, COIN };
enum GameState { START, PLAY, EXITE, PAUSE, GAME_OVER, OUT, CHOOSE_PLAYER };
enum Direction { UP, DOWN, LEFT, RIGHT };

struct Object {
	G_Rect position;
	G_Texture* texture;
	ObjectType type;
	SDL_Point tile;
	bool isMoving = false;
	Direction dir;
	G_Sound* sound = NULL;
	union {
		int moveSpeed;
		int timer;
	};
};

struct Tile {
	TileType type;
	G_Rect position;
	G_Texture* texture;
};

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
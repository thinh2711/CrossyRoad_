// GameInitialization.h
#ifndef GAME_INITIALIZATION_H
#define GAME_INITIALIZATION_H

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

//For Fonts , Buttons , logo , ... !
struct Element {
	G_Rect position;
	G_Texture* texture;
};

void load();
void initTiles();

#endif // GAME_INITIALIZATION_H
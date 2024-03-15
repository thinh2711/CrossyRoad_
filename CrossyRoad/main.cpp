#include "Genio.h"
#include <cstdlib>
#include <ctime>
#include <deque>

using namespace std;

enum TileType { GRASS, WATER, ROAD, RAIL, TREE };
enum ObjectType { PLAYER, CAR, TRAIN, STICK, LAMP, EAGLE, COIN };
enum GameState { START, PLAY, EXITE, PAUSE, GAME_OVER, OUT, CHOOSE_PLAYER };
enum Direction { UP, DOWN, LEFT, RIGHT };

#include "GameInitialization.h"
#include "Genio.h"
#include "Rendering.h"
#include "GameLogic.h"


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

Tile** map1 = NULL;
GameState state = START;
G_Rect windowPos;
G_Rect realPlayerClip = { 30,0,40,100 };
Object Player;
Tile grassTile, treeTile, waterTile, roadTile, railTile;
Object Car, Stick, Train, Lamp, Eagle, Coin;
G_Texture* car2Texture;
G_Texture* car3Texture;
G_Texture* redLampTexture;
G_Texture* cowTexture;
G_Texture* sheepTexture;
G_Texture* pigTexture;
Element ScoreText, Logo, TryAgainButton, ClickButton, GameOverText, PauseButton, PlayerChooseButton, PlayerButton, CoinText, TopScoreText;
G_Font* font;
G_Sound* clickSound;



#include "GameLogic.h"
#include "windows.h"

using namespace std;

const int PLAY_TIME = 90;              
const int SCREEN_WIDTH = 950;           
const int SCREEN_HEIGHT = 900;          
const string WINDOW_TITLE = "HANG MAN";  

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    WINDOWS* window =  new WINDOWS(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    srand(time(0));                            // random seeds
    HangmanGame* hangman = new HangmanGame(window, PLAY_TIME);  // initialize game
    window->Font("Font.ttf", 30);               // text font and size
    while (hangman->gameplay)                  // while player is playing game
    {
        hangman->startGame();                  // start a game
        do {                                   // initialize game loop for rendering
            hangman->renderGameSDL();          // render SDL game
            hangman->guessEvent();             // handle SDL keypress event
            hangman->handleGuess();            // handle game based on event
        } while (hangman->guessing());         // render game if the player is guessing
        hangman->gameOver();                   // handle game over data and render SDL
    }
    return 0;
}

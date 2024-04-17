#include "GameLogic.h"
#include "windows.h"
#include "SDL2/SDL_mixer.h"
using namespace std;

const int PLAY_TIME = 5;              
const int SCREEN_WIDTH = 950;           
const int SCREEN_HEIGHT = 900;          
const string WINDOW_TITLE = "HANG MAN";  

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *backgroundMusic = Mix_LoadMUS("sound/background.mp3");
    if (!backgroundMusic) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
    } else {
        Mix_PlayMusic(backgroundMusic, -1);
    }

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
            hangman->updateTimeLeft();         // update game time
        } while (hangman->guessing());         // render game if the player is guessing
        hangman->gameOver();                   // handle game over data and render SDL
    }
    Mix_FreeMusic(backgroundMusic);
    return 0;
}

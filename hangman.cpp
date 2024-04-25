#include "GameLogic.h"
#include "windows.h"
#include "SDL2/SDL_mixer.h"
using namespace std;

const int PLAY_TIME = 100;              
const int SCREEN_WIDTH = 1000;           
const int SCREEN_HEIGHT = 900;          
const string WINDOW_TITLE = "HANG MAN";  

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *backgroundMusic = Mix_LoadMUS("sound/background.mp3");
    if (!backgroundMusic) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
    }
    Mix_Music *menuMusic = Mix_LoadMUS("sound/menu.wav"); // Load menu music
    if (!menuMusic) {
        cout << "Failed to load menu music! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    WINDOWS* window =  new WINDOWS(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    srand(time(0));                                             // random seeds
    HangmanGame* hangman = new HangmanGame(window, PLAY_TIME);  // initialize game
    window->Font("Font.ttf", 25);                               // text font and size

    Mix_PlayMusic(menuMusic, -1);                               // Play menu music
    window->Menu();                                             // render menu
    Mix_HaltMusic();                                            // stop menu music

    if(window->Menu() == true) {                                // if player choose to play game
        while (hangman->gameplay)                               // while player is playing game
        {
            Mix_PlayMusic(backgroundMusic, -1);                 // play background music
            
            hangman->startGame();                               // start a game
            do {                                                // initialize game loop for rendering
                
                hangman->renderGameSDL();                       // render SDL game
                hangman->guessEvent();                          // handle SDL keypress event
                hangman->handleGuess();                         // handle game based on event
                hangman->updateTimeLeft();                      // update game time
            } while (hangman->guessing());                      // render game if the player is guessing
            Mix_HaltMusic();                                    // stop background music
            hangman->gameOver();                                // handle game over data and render SDL
        }
        Mix_FreeMusic(backgroundMusic);
        Mix_FreeMusic(menuMusic);
    }
    return 0;
}

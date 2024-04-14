#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <ctime>
#include <string>

#include "windows.h"
using namespace std;

//Hangman game class
class HangmanGame {
    const int MAX_BAD_GUESS = 7;  
    string fileName; 
    string name;
    int diff = -1;  
    WINDOWS* window;

    int playTime;                 // Playing time of Game
    int countwin;                 // Number of win games
    int countloss;                // Number of loss games
    bool quit;                    // If player want to quit Game
    string secretword;            // The random word has to be guessed
    char guessChar;               // Character player pressed
    string guessedWord;           // Guessed word include suggested characters
    string guessedString;         // Guessed word exclude suggested characters
    int badGuessCount;            // Number of bad guesses made by the player
    int suggested;                // Number of suggested characters
    int maxSuggest;               // Maximum number of suggestions
    string badGuess;              // Bad guessed characters


   public:
    HangmanGame(WINDOWS* ,int);
    bool gameplay;
    void startGame();                   // initialize new Game
    void initWord();                    // initialize word need guessing
    void getSuggest();                  // get a suggestion
    void updateGuessedWord();           // update guessed word
    void updateSuggest();               // update maximum number of suggestions
    bool guessing();                    // determine whether the player is guessing or not
    void guessEvent();                  // handle guessing event
    void handleGuess();                 // handle guessing character
    void badGuessed();                  // handle bad guessed
    void gameOver();                    // initialize game over
    void checkContinue(SDL_Event);      // check if player want to continue playing game
    
    void renderGameSDL();               // render playing game window
    void renderGameOverSDL(int);        // render game over window
    void createGameOverSDL();           // initialize game over loop for rendering

    void choosefileName();              // Choose file of random word
    void renderfileName();              // render file window
    void choosefileNameEvent();         // handle choose file event
    void chooseDiff();                  // Choose the difficulty of random word
    void renderDiff();                  // render difficulty window
    void chooseDiffEvent();             // handle choose difficulty event
};

#endif  // GAMELOGIC_H
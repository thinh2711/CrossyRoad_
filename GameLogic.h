#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <ctime>
#include <string>

#include "windows.h"
using namespace std;

//Hangman game class
class HangmanGame {
    WINDOWS* window;
    const int MAX_BAD_GUESS = 7;
    string word;
    string secretWord;
    string correctChars;
    string incorrectChars;
    int incorrectGuess;
    bool isGameOver;
    bool isGameWon;

   public:
    Game(WINDOWS* window_);
    void startGame();
    void processInput(char ch);
    void drawGame();
    void drawGameOver();
    void drawGameWon();
    void drawGameLost();
    void drawSecretWord();
    void drawIncorrectChars();
    void drawHangman();
    void drawHangmanBody();
    void drawHangmanHead();
    void drawHangmanBodyPart(int x1, int y1, int x2, int y2);
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
    void drawHangmanArm();
    void drawHangmanLeg();
    void drawHangmanRope();
    void drawHangmanBase();
    void drawHangmanPole();
    void drawHangmanHead();
    void drawHangmanBody();
}

#endif  // GAMELOGIC_H
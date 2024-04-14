#include "GameLogic.h"

#include <ctime>
#include <unordered_map>

#include "windows.h"
#include "diff.h"

using namespace std;

HangmanGame::HangmanGame(WINDOWS* WINDOWS, int time) : SDL(WINDOWS), playTime(time) {
    gameplay = true;
    countwin = 0;
    countloss = 0;
}
void HangmanGame::initWord() {
    word = chooseWord(fileName, diff);
    if (word.empty()) {
        cout << "No word available in " << fileName << endl;
        gameplay = false;
        quit = true;
    }
}

void HangmanGame::guessEvent() {
    SDL_Event event;
    guessChar = ' ';
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameplay = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            gameplay = false;
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName == "Escape")
                gameplay = false;
            else if (keyName == "Space")
                guessChar = '$';
            else if (keyName.length() == 1 && keyName[0] >= 'A' && keyName[0] <= 'Z')
                guessChar = keyName[0];
        }
    }
}

void HangmanGame::badGuessed() {
    badGuessCount++;
    badGuess += guessChar;
    guessedString += guessChar;
}

bool HangmanGame::guessing() {
    if(guessedWord != secretword && badGuessCount < MAX_BAD_GUESS && gameplay) {
        return true;
    }
    return false;
}\

void HangmanGame::updateSuggest() {
    if (suggested < maxSuggest) 
    {
        int suggest = 0, sizeofsecret = guessedWord.length();
        unordered_map<char, int> map;
        for (int i = 0; i < sizeofsecret; i++)
            {
                if (guessedWord[i] == '-')
                    map[secretword[i]]++;
            }
        suggest = map.size();
        maxSuggest = suggest / 2;
    }
    if (suggested > maxSuggest) 
    {
        maxSuggest = suggested;
    }
}

void HangmanGame::updateGuessedWord() {
    int size = guessedWord.length(), countguessChar = 0;
    for (int i = 0; i < size; i++) {
        if (secretword[i] == guessChar) {
            guessedWord[i] = guessChar;
            countguessChar++;
        }
    }
    guessedString += guessChar;
}

void HangmanGame::startGame() {
    quit = false;
    if(quit){
        return;
    }
    system("cls");
    
    initWord();
    guessedWord = string(secretword.length(), '-');
    guessChar = '';
    badGuessCount = 0;
    maxSuggest = 10;
    badGuess = "";
    suggested = 0;
    guessedString = "";
    
    for (unsigned int i = 0; i < word.length(); i++)
        {
            if (word[i] == ' ')
                guessedWord[i] = ' ';
        }
    updateSuggest();
}
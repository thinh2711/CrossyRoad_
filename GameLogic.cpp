#include "GameLogic.h"

#include <ctime>
#include <unordered_map>

#include "windows.h"
#include "diff.h"

using namespace std;

HangmanGame::HangmanGame(WINDOWS* WINDOWS, int time) : window(WINDOWS), playTime(time) {
    gameplay = true;
    countwin = 0;
    countloss = 0;
}

void HangmanGame::initWord() {
    secretword = chooseWord(fileName, diff);
    if (secretword.empty()) {
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
}

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
    if (suggested >= maxSuggest) 
    {
        maxSuggest = suggested;
    }
}

void HangmanGame::updateGuessedWord() {
    int size = guessedWord.length(), countguessChar = 0;
    for (int i = 0; i < size; i++) {
        if (secretword[i] == guessChar) 
        {
            guessedWord[i] = guessChar;
            countguessChar++;
        }
    }
    guessedString += guessChar;
}

void HangmanGame::startGame() {
    quit = false;
    if(quit)
    {
        return;
    }
    system("cls");
    
    initWord();
    guessedWord = string(secretword.length(), '-');
    guessChar = ' ';
    badGuessCount = 0;
    maxSuggest = 10;
    badGuess = "";
    suggested = 0;
    guessedString = "";
    
    for (unsigned int i = 0; i < secretword.length(); i++)
        {
            if (secretword[i] == ' ')
                guessedWord[i] = ' ';
        }
    updateSuggest();
}

void HangmanGame::gameOver() {
    if (guessedWord != secretword)
        {
            countloss++;
        }
    else
        countwin++;
}

void HangmanGame::getSuggest() {
    if (suggested < maxSuggest) 
    {
        suggested++;
        while (1) 
        {
            int i = rand() % guessedWord.length();
            if (guessedWord[i] == '-') 
            {
                guessChar = secretword[i];
                updateGuessedWord();
                break;
            }
        }
    }
}

void HangmanGame::renderGameSDL() {
    window->createImageBackground("hang" + to_string(badGuessCount) + ".png");

    window->createTextTexture("Win : " + to_string(countwin), 750, 45);
    window->createTextTexture("Loss: " + to_string(countloss), 750, 85);
    window->createTextTexture("Current Guess    :     " + guessedWord, 100, 750);
    window->createTextTexture("Bad Guesses      :     " + badGuess, 100, 800);
    window->createTextTexture("Used suggestions :     " + to_string(suggested) + "/" + to_string(maxSuggest) + "   (Press 'Space')", 100, 850);
    window->updateScreen();
}

void HangmanGame::checkContinue(SDL_Event e) {
    while (SDL_PollEvent(&e)) 
    {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) 
        {
            gameplay = false;
            quit = true;
        } else if (e.type == SDL_KEYUP &&
                   (e.key.keysym.sym == SDLK_RETURN ||
                    e.key.keysym.sym == SDLK_RETURN2 ||
                    e.key.keysym.sym == SDLK_KP_ENTER)) 
                    {
                        gameplay = true;
                        quit = true;
                    }
    }
}

void HangmanGame::choosefileName() {
    fileName = "";
    while (fileName == "" && gameplay && !quit) {
        renderfileName();
        choosefileNameEvent();
    }
}

void HangmanGame::choosefileNameEvent() {
    SDL_Event event;
    if (SDL_WaitEvent(&event)) 
    {
        if (event.type == SDL_QUIT) 
        {
            gameplay = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) 
            {
                gameplay = false;
            } else if (event.type == SDL_KEYUP) 
                {
                    string key = SDL_GetKeyName(event.key.keysym.sym);
                    if (key.length() == 1 && key[0] >= '1' && key[0] <= '5')
                        {
                            switch (key[0])
                            {
                            case '1':
                                fileName = "all.txt";
                                name = "All fields";
                                break;
                            case '2':
                                fileName = "fruits.txt";
                                name = "Fruits";
                                break;
                            case '3':
                                fileName = "asia.txt";
                                name = "Asia Countries";
                                break;
                            case '4':
                                fileName = "jobs.txt";
                                name = "Jobs";
                                break;
                            case '5':
                                fileName = "plants.txt";
                                name = "Plants";
                                break;
                            }
                        }
                }
    }
}

void HangmanGame::renderfileName() {
    window->createImageBackground("hang0.png");
    window->createTextTexture("Choose word category:", 100, 50);
    window->createTextTexture("1. All fields", 150, 100);
    window->createTextTexture("2. Fruits", 150, 150);
    window->createTextTexture("3. Asia Countries", 150, 200);
    window->createTextTexture("4. Jobs", 150, 250);
    window->createTextTexture("5. Plants", 150, 300);
    window->updateScreen();
}

void HangmanGame::handleGuess() {
    if (guessChar == ' ') return;
    
    if (guessChar == '$')
        {
            getSuggest();
        }else if (contain(guessedString, guessChar))
            {
                return;
            }else if (contain(secretword, guessChar)) 
                {
                    updateGuessedWord();
                    updateSuggest();
                } else if (!contain(badGuess, guessChar)) 
                    {
                        badGuessed();
                    }
    
}

void HangmanGame::chooseDiffEvent() {
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameplay = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            gameplay = false;
        } else if (event.type == SDL_KEYUP) {
            string key = SDL_GetKeyName(event.key.keysym.sym);
            if (key.length() == 1 && key[0] >= '1' && key[0] <= '5')
                switch (key[0]) {
                    case '1':
                        diff = 0;
                        break;
                    case '2':
                        diff = 1;
                        break;
                }
        }
    }
}

void HangmanGame::renderDiff() {
    window->createImageBackground("hang0.png");
    window->createTextTexture("Category: " + name , 100, 50);
    window->createTextTexture("Choose word difficulty:", 100, 100);
    window->createTextTexture("1. Easy", 150, 150);
    window->createTextTexture("2. Hard", 150, 200);
    window->updateScreen();
}

void HangmanGame::chooseDiff() {
    diff = -1;
    while (diff == -1 && gameplay && !quit) {
        renderDifficulty();
        chooseDifficultyEvent();
    }
}
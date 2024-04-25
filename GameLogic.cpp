#include "GameLogic.h"

#include <ctime>
#include <unordered_map>
#include "SDL2/SDL_mixer.h"

#include "windows.h"
#include "diff.h"

using namespace std;

HangmanGame::HangmanGame(WINDOWS* WINDOWS, int time) : window(WINDOWS), playTime(time) {
    gameplay = true;
    countwin = 0;
    countloss = 0;
     // Khởi tạo SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Khởi tạo hệ thống âm thanh
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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
    if(guessedWord != secretword && badGuessCount < MAX_BAD_GUESS && gameplay && !quit && timeLeft > 0) {
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
    renderPlane(guessChar, countguessChar);
}

void HangmanGame::startGame() {
    quit = false;
    if(quit)
    {
        return;
    }
    system("cls");
    chooseDiff();
    choosefileName();
    
    initWord();
    guessedWord = string(secretword.length(), '-');
    guessChar = ' ';
    badGuessCount = 0;
    maxSuggest = 10;
    badGuess = "";
    suggested = 0;
    guessedString = "";
    animatedTime = 0;
    time(&startTime);

    for (unsigned int i = 0; i < secretword.length(); i++)
        {
            if (secretword[i] == ' ')
            {
                guessedWord[i] = ' ';
            }
                
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
    createGameOverSDL();
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
    window->createTextTexture("Time: " + to_string(timeLeft), 700, 5);
    window->createTextTexture("Win : " + to_string(countwin), 700, 45);
    window->createTextTexture("Loss: " + to_string(countloss), 700, 85);
    window->createTextTexture( name, 700, 125);
    window->createTextTexture("Current Guess    :     " + guessedWord, 100, 750);
    window->createTextTexture("Bad Guesses      :     " + badGuess, 100, 800);
    window->createTextTexture("Used suggestions :     " + to_string(suggested) + "/" + to_string(maxSuggest) + "   (Press 'Space')", 100, 850);
    window->updateScreen();
    SDL_Delay(15);
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
        if(diff == 0 )
        {
            renderfileNameEasy();
            choosefileNameEvent();
        }
        else if(diff == 1)
        {
            renderfileNameHard();
            choosefileNameEventHard();
        }
    }
}

void HangmanGame::choosefileNameEvent() {
    
    SDL_Event event;
    Mix_Chunk *all = Mix_LoadWAV("sound/All fields.wav");
    Mix_Chunk *fruits = Mix_LoadWAV("sound/Fruits Easy.wav");
    Mix_Chunk *asia = Mix_LoadWAV("sound/Asia Countries Easy.wav");
    Mix_Chunk *jobs = Mix_LoadWAV("sound/Jobs Easy.wav");
    Mix_Chunk *plants = Mix_LoadWAV("sound/Plants Easy.wav");
    if (SDL_WaitEvent(&event)) 
    {
        if (event.type == SDL_QUIT) 
        {
            gameplay = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) 
            {
                gameplay = false;
                exit(0);
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
                            Mix_PlayChannel(-1, all, 0);
                            SDL_Delay(1000);
                            break;
                        case '2':
                            fileName = "fruits.txt";
                            name = "Fruits Easy";
                            Mix_PlayChannel(-1, fruits, 0);
                            SDL_Delay(1000);
                                break;
                        case '3':
                            fileName = "asia.txt";
                            name = "Asia Countries Easy";
                            Mix_PlayChannel(-1, asia, 0);
                            SDL_Delay(1000);
                            break;
                        case '4':
                            fileName = "jobs.txt";
                            name = "Jobs Easy";
                            Mix_PlayChannel(-1, jobs, 0);
                            SDL_Delay(1000);
                            break;
                        case '5':
                            fileName = "plants.txt";
                            name = "Plants Easy";
                            Mix_PlayChannel(-1, plants, 0);
                            SDL_Delay(1000);
                            break;
                        }
                    }
                    else if (key.length() == 1 && key[0] == '6')
                    {
                        chooseDiff();
                    }
                }
    }

    Mix_FreeChunk(all);
    Mix_FreeChunk(fruits);
    Mix_FreeChunk(asia);
    Mix_FreeChunk(jobs);
    Mix_FreeChunk(plants);
}

void HangmanGame::choosefileNameEventHard() {
    SDL_Event event;
    Mix_Chunk *all = Mix_LoadWAV("sound/All fields.wav");
    Mix_Chunk *fruits = Mix_LoadWAV("sound/Fruits Hard.wav");
    Mix_Chunk *asia = Mix_LoadWAV("sound/Asia Countries Hard.wav");
    Mix_Chunk *jobs = Mix_LoadWAV("sound/Jobs Hard.wav");
    Mix_Chunk *plants = Mix_LoadWAV("sound/Plants Hard.wav");
    if (!all || !fruits || !asia || !jobs || !plants) 
    {
        window->wrongSDL(cout, "Mix_LoadWAV", true);
    }
    if (SDL_WaitEvent(&event)) 
    {
        if (event.type == SDL_QUIT) 
        {
            gameplay = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) 
            {
                gameplay = false;
                exit(0);
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
                            Mix_PlayChannel(-1, all, 0);
                            SDL_Delay(1000);
                            break;
                        case '2':
                            fileName = "fruitsDiff.txt";
                            name = "Fruits Hard";
                            Mix_PlayChannel(-1, fruits, 0);
                            SDL_Delay(1000);
                            break;
                        case '3':
                            fileName = "asiaDiff.txt";
                            name = "Asia Countries Hard";
                            Mix_PlayChannel(-1, asia, 0);
                            SDL_Delay(1000);
                            break;
                        case '4':
                            fileName = "jobsDiff.txt";
                            name = "Jobs Hard";
                            Mix_PlayChannel(-1, jobs , 0);
                            SDL_Delay(1000);
                            break;
                        case '5':
                            fileName = "plantsDiff.txt";
                            name = "Plants Hard";
                            Mix_PlayChannel(-1, plants, 0);
                            SDL_Delay(1000);
                            break;
                        
                        }
                    }
                    else if (key.length() == 1 && key[0] == '6')
                    {
                        chooseDiff();
                    }
                    
                }
    }
    Mix_FreeChunk(all);
    Mix_FreeChunk(fruits);
    Mix_FreeChunk(asia);
    Mix_FreeChunk(jobs);
    Mix_FreeChunk(plants);
}

void HangmanGame::renderfileNameEasy() {
    window->createImageBackground("hang0.png");
    window->createTextTexture("Choose word category:", 100, 50);
    window->createTextTexture("Press 1 : All fields", 150, 100);
    window->createTextTexture("Press 2 : Fruits", 150, 150);
    window->createTextTexture("Press 3 : Asia Countries", 150, 200);
    window->createTextTexture("Press 4 : Jobs", 150, 250);
    window->createTextTexture("Press 5 : Plants", 150, 300);
    window->createTextTexture("Press 6 : Back to choose difficulty", 150, 350);
    window->updateScreen();
}

void HangmanGame::renderfileNameHard() {
    window->createImageBackground("hang0.png");
    window->createTextTexture("Choose word category:", 100, 50);
    window->createTextTexture("Press 1 : All fields", 150, 100);
    window->createTextTexture("Press 2 : Fruits Hard", 150, 150);
    window->createTextTexture("Press 3 : Asia Countries Hard", 150, 200);
    window->createTextTexture("Press 4 : Jobs Hard", 150, 250);
    window->createTextTexture("Press 5 : Plants Hard", 150, 300);
    window->createTextTexture("Press 6 : Back to choose difficulty", 150, 350);
    window->updateScreen();
    
}

void HangmanGame::handleGuess() {
    if (guessChar == ' ') 
        return;
    
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
                        renderPlane(guessChar, 0);
                    }
    
}

void HangmanGame::chooseDiffEvent() {
    SDL_Event event;
    Mix_Chunk *easy = Mix_LoadWAV("sound/easy.wav");
    Mix_Chunk *hard = Mix_LoadWAV("sound/difficult.wav");
    if (SDL_WaitEvent(&event)) 
    {
        if (event.type == SDL_QUIT) {
            gameplay = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            gameplay = false;
            exit(0);
        } else if (event.type == SDL_KEYUP) {
            string key = SDL_GetKeyName(event.key.keysym.sym);
            if (key.length() == 1 && key[0] >= '1' && key[0] <= '2')
            {
                switch (key[0]) {
                    case '1':
                        diff = 0;
                        Mix_PlayChannel(-1, easy, 0);
                        SDL_Delay(1000);
                        break;
                    case '2':
                        diff = 1;
                        Mix_PlayChannel(-1, hard, 0);  
                        SDL_Delay(1000);
                        break;
                }
            }
        }
    }
    Mix_FreeChunk(easy);
    Mix_FreeChunk(hard);
}

void HangmanGame::renderDiff() {
    window->createImageBackground("hang0.png");
    // window->createTextTexture("Category: " + name , 100, 50);
    window->createTextTexture("Choose word difficulty:", 100, 100);
    window->createTextTexture("Press 1 : Easy", 150, 150);
    window->createTextTexture("Press 2 : Hard", 150, 200);
    window->updateScreen();
}

void HangmanGame::chooseDiff() {
    diff = -1;
    while (diff == -1 && gameplay && !quit) {
        renderDiff();
        chooseDiffEvent();
    }
}

void HangmanGame::renderGameOverSDL(int imageIndx) {
    string status;
    if (guessedWord == secretword) 
    {
        status = "free";
    } else {
        status = "hanged";
    }
    window->createImageBackground(status + to_string(imageIndx) + ".png");
    if (timeLeft <= 0)
    {
        window->createTextTexture("Time Up!!!", 700, 5);
    }
    window->createTextTexture("Win : " + to_string(countwin), 700, 45);
    window->createTextTexture("Loss: " + to_string(countloss), 700, 85);
    window->createTextTexture( name, 700, 125);
    
    if (guessedWord == secretword)
    {
        window->createTextTexture("Congratulations!!! You are free.", 100, 750);
    }
    else   {
        window->createTextTexture("Game Over!!! You are hanged!", 100, 750);
    }
    window->createTextTexture("Correct word: " + secretword, 100, 800);
    window->createTextTexture("Press 'Enter' to keep playing, 'ESC' to exit.", 100, 850);
    window->updateScreen();
}

void HangmanGame::createGameOverSDL() {
    int imageIndx = 0;

    Mix_Chunk *gameOverSound = Mix_LoadWAV("sound/gameover.wav");
    if (!gameOverSound) {
        window->wrongSDL(cout, "Mix_LoadWAV", true);
    }
    Mix_Chunk *winSound = Mix_LoadWAV("sound/victory.wav");
    if(!winSound)
    {
        window->wrongSDL(cout, "Mix_LoadWAV", true);
    }
    while (!quit) {
        SDL_Event e;
        checkContinue(e);
        renderGameOverSDL(imageIndx);
        SDL_Delay(200);
        ++imageIndx %= 4;

        if(guessedWord == secretword )
        {
            // Phát âm thanh
            Mix_PlayChannel(-1, winSound, 0);

            // Điều chỉnh tốc độ
            SDL_Delay(10);
        }
        else 
        {
            Mix_PlayChannel(-1, gameOverSound, 0);
            SDL_Delay(10);
        }
        
    }

    // Giải phóng tài nguyên âm thanh
    Mix_FreeChunk(gameOverSound);
    Mix_FreeChunk(winSound);
}

void HangmanGame::planeEvent(SDL_Event e, bool& skip) {
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
            skip = true;
        if (e.type == SDL_QUIT) {
            gameplay = false;
            quit = true;
            skip = true;
        }
    }
}

void HangmanGame::updateTimeLeft() {
    time_t now_;
    time(&now_);
    timeLeft = playTime - difftime(now_, startTime) + animatedTime;
}

void HangmanGame::renderPlane(char guessedChar, int num) {
    time_t Start, End;
    time(&Start);
    int i = -300;
    bool check = false;

    Mix_PauseMusic(); // Tạm dừng nhạc nền

    Mix_Chunk *planeSound = Mix_LoadWAV("sound/plane.wav");
    if (!planeSound) {
        window->wrongSDL(cout, "Mix_LoadWAV", true);
    }

    while (i < 1000 && !check) {
        SDL_Event event;
        planeEvent(event, check);
        window->createImageBackground("hang0.png");
        window->createImage("plane.png", i, 0);
        window->createTextTexture(string("There ") + (num == 1 ? "is " : "are ") + to_string(num) + " of " + guessedChar, i + 165, 215);
        window->createTextTexture("Press 'Space' to skip", 300, 850);
        window->updateScreen();
        i += 5;

        // Phát âm thanh
        Mix_PlayChannel(-1, planeSound, 0);

        // Điều chỉnh tốc độ
        SDL_Delay(10);
    }

    Mix_ResumeMusic(); // Tiếp tục phát nhạc nền

    time(&End);
    animatedTime += difftime(End, Start);

    // Giải phóng tài nguyên âm thanh
    Mix_FreeChunk(planeSound);
}


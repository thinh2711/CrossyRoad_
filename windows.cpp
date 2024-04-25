#include "windows.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

#include "draw.h"
using namespace std;

WINDOWS::WINDOWS(string title_, int width_, int height_) : title(title_), width(width_), height(height_) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        wrongSDL(cout, "SDL_Init", true);
    if (TTF_Init() < 0)
        wrongSDL(cout, "TTF_Init", true);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        wrongSDL(cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        wrongSDL(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, width, height);
}

WINDOWS::~WINDOWS() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void WINDOWS::wrongSDL(ostream& os, const string& msg, bool check) {
    os << msg << " Error: " << SDL_GetError() << endl;
    if (check) {
        SDL_Quit();
        exit(1);
    }
}

void WINDOWS::Font(string a, int size) {
    font = TTF_OpenFont(a.c_str(), size);
    draw = new DRAW(window, renderer, font);
}

void WINDOWS::createImage(string fileName, int x_, int y_) {
    SDL_Rect srcRest;
    SDL_Rect desRect;
    SDL_Texture* texture = NULL;
    texture = draw->loadImage("image/" + fileName, &srcRest, &desRect, x_, y_);
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
    SDL_DestroyTexture(texture);
}

void WINDOWS::createImageBackground(string fileName) {
    SDL_Texture* texture = NULL;
    texture = draw->loadTexture("image/" + fileName);
    draw->createImage(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}

void WINDOWS::createTextTexture(string text, int x_, int y_) {
    SDL_Rect srcRest;
    SDL_Rect desRect;
    SDL_Texture* texture = NULL;
    texture = draw->textTexture(text, &srcRest, &desRect, x_, y_);
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
    SDL_DestroyTexture(texture);
}

void WINDOWS::updateScreen() {
    SDL_RenderPresent(renderer);
}

bool WINDOWS::Menu() {
    bool quit = false;
    SDL_Event e;
    SDL_Texture* menuTexture = draw->loadTexture("image/menu.bmp");
    Mix_Chunk *click = Mix_LoadWAV("sound/select.wav");

    // Render texture lên màn hình
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);

    while (!quit)
    {
        // Xử lý các sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Xử lý sự kiện nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN ) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                // Kiểm tra xem chuột có nằm trong vùng ô vuông không (ví dụ: ô vuông có tọa độ (100, 100) và kích thước 50x50)
                if (mouseX >= 831 && mouseX <= 903 && mouseY >= 718 && mouseY <= 792) {
                    Mix_PlayChannel(-1, click, 0);
                    Mix_VolumeChunk(click, 200);
                    // Người dùng nhấp chuột vào ô vuông, xử lý tương ứng ở đây
                    cout << "Clicked on square!" << endl;
                    quit = true;
                    return quit;
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                // Kiểm tra xem phím nhấn có phải là ESC hay không
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                        
                    // Người dùng nhấn phím ESC, thoát khỏi vòng lặp
                    exit(0);
                }
            }
        }
    
    }
    Mix_FreeChunk(click);
    return quit;
}

#include "windows.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "draw.h"
using namespace std;


WINDOWS::~WINDOWS() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void WINDOWS::wrongSDL(ostream& os, const string& msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void WINDOWS::createImage(string fileName, int x, int y) {
    SDL_Rect srcRest;
    SDL_Rect desRect;
    SDL_Texture* texture = NULL;
    texture = draw->loadImage("image\\" + fileName, &srcRest, &desRect, x, y);
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
    SDL_DestroyTexture(texture);
}
void WINDOWS::createImageBackground(string fileName) {
    SDL_Texture* texture = NULL;
    texture = draw->loadTexture("image\\" + fileName);
    draw->createImage(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}
void WINDOWS::createTextTexture(string text, int x, int y) {
    SDL_Rect srcRest;
    SDL_Rect desRect;
    SDL_Texture* texture = NULL;
    texture = draw->textTexture(text, &srcRest, &desRect, x, y);
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
    SDL_DestroyTexture(texture);
}
void WINDOWS::updateScreen() {
    SDL_RenderPresent(renderer);
}


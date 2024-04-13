#include "draw.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

void DRAW::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void DRAW::setAngle(float angle) {
    this->angle = angle - floor(angle / 360) * 360;
}

void DRAW::setColor(SDL_Color color) {
    this->color = color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void DRAW::clearWithBgColor(SDL_Color bgColor) {
    SDL_Color curColor = color;
    setColor(bgColor);
    SDL_RenderClear(renderer);
    setColor(curColor);
}

SDL_Texture* DRAW::loadTexture(string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

SDL_Texture* DRAW::loadImage(string path, SDL_Rect* srcRest, SDL_Rect* desRect, float _x, float _y) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }

    SDL_QueryTexture(newTexture, NULL, NULL, &srcRest->w, &srcRest->h);
    srcRest->x = 0;
    srcRest->y = 0;
    desRect->x = _x;
    desRect->y = _y;
    desRect->w = srcRest->w;
    desRect->h = srcRest->h;
    return newTexture;
}

SDL_Texture* DRAW::textTexture(string text, SDL_Rect* srcRest, SDL_Rect* desRect, float _x, float _y) {
    SDL_Color a = {0, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), a);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    TTF_SizeText(font, text.c_str(), &srcRest->w, &srcRest->h);
    srcRest->x = 0;
    srcRest->y = 0;
    desRect->x = _x;
    desRect->y = _y;
    desRect->w = srcRest->w;
    desRect->h = srcRest->h;
    return texture;
}
bool DRAW::createImage(SDL_Texture* texture) {
    if (texture == NULL) return false;
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    return true;
}

DRAW::DRAW(SDL_Window* window = nullptr, SDL_Renderer* renderer_ = nullptr, TTF_Font* font_ = nullptr) : renderer(renderer_), font(font_) {
    if (window == nullptr) return;
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);

    setPosition(width / 2, height / 2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(WHITE_COLOR);
}
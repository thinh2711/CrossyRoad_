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

#ifndef WINDOWS_H
#define WINDOWS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "draw.h"
using namespace std;

class WINDOWS {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    DRAW* draw;
    string title;
    int width;
    int height;

   public:
    WINDOWS (string title_, int width_, int height_);
    ~WINDOWS();
    void wrongSDL(ostream& os, const string& msg, bool check);
    void Font(string a, int size);
    void createTextTexture(string text, int x_, int y_);
    void createImageBackground(string fileName);
    void createImage(string fileName, int x_, int y_);
    void updateScreen();
};

#endif  // WINDOWS_H
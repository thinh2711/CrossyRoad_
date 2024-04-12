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

    DRAW* draw;
    string title;
    int width;
    int height;

   public:
    WINDOWS(string title_, int width_, int height_);
    ~WINDOWS();
    void wrongSDL(ostream& os, const string& msg, bool fatal);

    void createTextTexture(string text, int x, int y);
    void createImageBackground(string fileName);
    void createImage(string fileName, int x, int y);
    void updateScreen();
};

#endif  // WINDOWS_H
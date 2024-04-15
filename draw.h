#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <string>

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

class DRAW {
    double x;
    double y;
    double angle;
    int width;
    int height;
    SDL_Color color;
    SDL_Renderer* renderer;
    TTF_Font* font;

   public:
    DRAW (SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);

    void setPosition(double x, double y);
    double getX() const 
    { 
        return x; 
    }
    double getY() const 
    { 
        return y; 
    }

    void setAngle(double angle);
    double getAngle() const 
    { 
        return angle; 
    }

    int getWidth() const 
    { 
        return width; 
    }
    int getHeight() const 
    { 
        return height; 
    }

    void setColor(SDL_Color color);
    SDL_Color getColor() const 
    { 
        return color; 
    }

    SDL_Renderer* getRenderer() const 
    { 
        return renderer; 
    }

    void clearWithBgColor(SDL_Color color);

    void moveForward(double length);
    void jumpForward(double length);
    void moveBackward(double length) 
    {
        moveForward(-length);
    }
    void jumpBackward(double length) 
    {
        jumpForward(-length);
    }
    void turnLeft(double angle)
    {
        setAngle(this->angle + angle);
    }
    void turnRight(double angle) 
    {
        turnLeft(-angle);
    }

    void getRandomColor();

    void drawCircle(double rad);
    void drawSquare(double size);
    void drawParallelogram(double size);

    SDL_Texture* loadTexture(std::string filepath);
    SDL_Texture* textTexture(std::string text, SDL_Rect* srcRest, SDL_Rect* desRect, double _x = 0, double _y = 0);
    SDL_Texture* loadImage(std::string text, SDL_Rect* srcRest, SDL_Rect* desRect, double _x = 0, double _y = 0);
    bool createImage(SDL_Texture* texture);
};

#endif
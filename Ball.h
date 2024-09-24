#ifndef BALL_H
#define BALL_H

#include "Vector2.h"
#include <SDL2/SDL.h>

struct Ball
{
    int radius;
    Vector2 position;
    Vector2 velocity;

    void UpdatePosition(float deltaTime);
    void DrawBall(SDL_Renderer* renderer);

    Ball(float xPos, float yPos, int radius);
    ~Ball();
};

#endif
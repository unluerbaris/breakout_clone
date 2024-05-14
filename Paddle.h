#ifndef PADDLE_H
#define PADDLE_H

#include "Vector2.h"

struct Paddle
{
    Vector2 position;
    Vector2 velocity;
    int width;
    int height;
    int speed;

    void UpdatePosition(float deltaTime);

    Paddle(float xPos, float yPos, int width, int height, int speed);
    ~Paddle();
};

#endif
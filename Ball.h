#ifndef BALL_H
#define BALL_H

#include "Vector2.h"

struct Ball
{
    int radius;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    void Move(float deltaTime);

    Ball(float xPos, float yPos, int radius);
    ~Ball();
};

#endif
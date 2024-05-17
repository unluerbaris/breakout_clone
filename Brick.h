#ifndef BRICK_H
#define BRICK_H

#include "Vector2.h"

struct Brick
{
    Vector2 position;
    int width;
    int height;

    Brick(float xPos, float yPos, int width, int height);
    ~Brick();
};

#endif
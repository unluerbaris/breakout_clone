#ifndef BRICK_H
#define BRICK_H

#include "Vector2.h"

struct Brick
{
    Vector2 position;
    int xPos;
    int yPos;
    int width;
    int height;

    Brick(int xPos, int yPos, int width, int height);
    ~Brick();
};

#endif
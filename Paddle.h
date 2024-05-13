#ifndef PADDLE_H
#define PADDLE_H

struct Paddle
{
    float xPos;
    float yPos;
    int width;
    int height;

    Paddle(float xPos, float yPos, int width, int height);
    ~Paddle();
};

#endif
#ifndef BALL_H
#define BALL_H

struct Ball
{
    int radius;
    float xPos;
    float yPos;

    Ball(float xPos, float yPos, int radius);
    ~Ball();
};

#endif
#include "Ball.h"
#include <iostream>

Ball::Ball(float xPos, float yPos, int radius)
{
    this->position = Vector2(xPos, yPos);
    this->velocity = Vector2(0.0, 0.0);
    this->radius = radius;
    std::cout << "ball is created" << std::endl;
}

Ball::~Ball()
{
   std::cout << "ball is destroyed" << std::endl;
}

void Ball::UpdatePosition(float deltaTime)
{
    this->position.x += this->velocity.x * deltaTime;
    this->position.y += this->velocity.y * deltaTime;
}

// Midpoint Circle Algorithm is used for drawing a circle
void Ball::DrawBall(SDL_Renderer* renderer)
{
    for (int innerCircleRadius = 0; innerCircleRadius < this->radius; innerCircleRadius++)
    {
        std::cout << innerCircleRadius << std::endl;
        int x = (innerCircleRadius - 1);
        int y = 0;
        int tx = 1;
        int ty = 1;
        int error = (tx - (innerCircleRadius * 2));

        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, this->position.x + x, this->position.y - y);
            SDL_RenderDrawPoint(renderer, this->position.x + x, this->position.y + y);
            SDL_RenderDrawPoint(renderer, this->position.x - x, this->position.y - y);
            SDL_RenderDrawPoint(renderer, this->position.x - x, this->position.y + y);
            SDL_RenderDrawPoint(renderer, this->position.x + y, this->position.y - x);
            SDL_RenderDrawPoint(renderer, this->position.x + y, this->position.y + x);
            SDL_RenderDrawPoint(renderer, this->position.x - y, this->position.y - x);
            SDL_RenderDrawPoint(renderer, this->position.x - y, this->position.y + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - (innerCircleRadius * 2));
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}
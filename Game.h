#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class Game
{
    private:
        Ball* ball;
        Paddle* paddle;
        Brick* bricks[10];
        bool isRunning = false;

        // Game
        const int NUMBER_OF_BRICKS = 10;

        // Screen and FPS
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 600;
        const int FPS = 60;
        const int MILLISECS_PER_FRAME = 1000 / FPS;
        const int PIXELS_PER_METER = 50;
        
    public:
        Game() = default;
        ~Game() = default;
        bool InitializeWindow();
        bool IsRunning();
        void Setup();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
};

#endif
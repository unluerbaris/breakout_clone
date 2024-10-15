#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class Game
{
    private:
        // Game
        constexpr static int NUMBER_OF_BRICKS = 39;
        const int GAP_BETWEEN_BRICKS = 10;
        const int SCREEN_EDGE_OFFSET = 50;
        const int FIXED_BRICK_WIDTH = 45;
        const int FIXED_BRICK_HEIGHT = 15;

        Ball* ball;
        Paddle* paddle;
        Brick* bricks[NUMBER_OF_BRICKS];
        bool isRunning = false;

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
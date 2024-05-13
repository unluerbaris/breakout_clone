#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Paddle.h"

class Game
{
    private:
        Ball* ball;
        Paddle* paddle;
        bool isRunning = false;

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
#ifndef GAME_H
#define GAME_H

#include "Ball.h"

class Game
{
    private:
        Ball* ball;
        bool isRunning = false;

        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 600;
        
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
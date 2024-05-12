#include "Game.h"

int main(int argc, char const *argv[])
{
    Game game;
    game.Setup();

    while (game.IsRunning())
    {
        game.ProcessInput();
        game.Update();
        game.Render();
    }
    game.Destroy();

    return 0;
}

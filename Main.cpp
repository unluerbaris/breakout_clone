#include <iostream>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

bool isRunning = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Initialize SDL Window
bool InitializeWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL!" << std::endl;
        return false;
    }

    // Create Window
    window = SDL_CreateWindow(
        "BreakOut",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    if (!window)
    {
        std::cerr << "Error creating SDL window!" << std::endl;
        return false;
    }
    
    // Create Renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer)
    {
        std::cerr << "Error creating SDL renderer!" << std::endl;
        return false;
    }
    return true;
}

void Setup()
{
    // Initialize game objects
}

void ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
                break;
        }
    }
}

void Update()
{
    // Update game objects
}

void Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char const *argv[])
{
    isRunning = InitializeWindow();
    Setup();

    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
    Destroy();

    std::cout << isRunning << std::endl;
    return 0;
}

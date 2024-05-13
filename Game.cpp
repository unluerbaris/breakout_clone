#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool Game::IsRunning()
{
    return isRunning;
}

// Initialize SDL Window
bool Game::InitializeWindow()
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

void Game::Setup()
{
    isRunning = InitializeWindow();

    // Initialize game objects
    ball = new Ball(400, 400, 6);   
    paddle = new Paddle(400, 550, 32, 5);
}

void Game::ProcessInput()
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

void Game::Update()
{
    // Update game objects
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw ball
    filledCircleColor(renderer, ball->xPos, ball->yPos, ball->radius, 0xFFFFFFFF);
    
    // Draw paddle
    boxColor(
        renderer, 
        (paddle->xPos - paddle->width), 
        (paddle->yPos - paddle->height), 
        (paddle->xPos + paddle->width),
        (paddle->yPos + paddle->height),
        0xFFFFFFFF
    );

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    delete ball;
    delete paddle;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
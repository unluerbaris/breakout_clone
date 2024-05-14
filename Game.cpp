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

    // Initialize Ball
    ball = new Ball(400, 400, 6);
    ball->velocity.x = 6 * PIXELS_PER_METER;
    ball->velocity.y = 3 * PIXELS_PER_METER;

    // Initialize PAddle
    paddle = new Paddle(400, 550, 32, 5, 10);
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
                if (event.key.keysym.sym == SDLK_RIGHT) paddle->velocity.x = paddle->speed * PIXELS_PER_METER;
                if (event.key.keysym.sym == SDLK_LEFT) paddle->velocity.x = -1 * paddle->speed * PIXELS_PER_METER;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_RIGHT) paddle->velocity.x = 0;
                if (event.key.keysym.sym == SDLK_LEFT) paddle->velocity.x = 0;
                break;
        }
    }
}

void Game::Update()
{
    // Wait some time until the reach the target frame time in milliseconds
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0) SDL_Delay(timeToWait);

    // Calculate the deltatime in seconds
    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
    if (deltaTime > 0.016) deltaTime = 0.016;

    // Set the time of the current frame to be used in the next one
    timePreviousFrame = SDL_GetTicks();

    ball->UpdatePosition(deltaTime);
    paddle->UpdatePosition(deltaTime);

    // Screen Borders for Ball
    if (ball->position.x - ball->radius <= 0) {
        ball->position.x = ball->radius;
        ball->velocity.x *= -1;
    } else if (ball->position.x + ball->radius >= WINDOW_WIDTH) {
        ball->position.x = WINDOW_WIDTH - ball->radius;
        ball->velocity.x *= -1;
    }
    if (ball->position.y - ball->radius <= 0) {
        ball->position.y = ball->radius;
        ball->velocity.y *= -1;
    } else if (ball->position.y + ball->radius >= WINDOW_HEIGHT) {
        ball->position.y = WINDOW_HEIGHT - ball->radius;
        ball->velocity.y *= -1;
    }

    // Ball and Paddle Collision
    if (ball->position.y + ball->radius >= paddle->position.y - paddle->height 
        && ball->position.x + ball->radius <= paddle->position.x + paddle->width
        && ball->position.x - ball->radius >= paddle->position.x - paddle->width) {
        ball->velocity.y *= -1;
    }

    // Screen Borders for Paddle
    if (paddle->position.x - paddle->width < 0) {
        paddle->position.x = paddle->width;
    } else if (paddle->position.x + paddle->width > WINDOW_WIDTH) {
        paddle->position.x = WINDOW_WIDTH - paddle->width;
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw ball
    filledCircleColor(renderer, ball->position.x, ball->position.y, ball->radius, 0xFFFFFFFF);
    
    // Draw paddle
    boxColor(
        renderer, 
        (paddle->position.x - paddle->width), 
        (paddle->position.y - paddle->height), 
        (paddle->position.x + paddle->width),
        (paddle->position.y + paddle->height),
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
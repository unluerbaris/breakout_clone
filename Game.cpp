#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

    // Initialize Paddle
    paddle = new Paddle(400, 550, 64, 10, 10);

    // Bigger paddle for tesing the collisions
    // paddle = new Paddle(400, 550, 256, 40, 10);

    // Initialize bricks
    for (int i = 0; i < NUMBER_OF_BRICKS; i++)
    {
        bricks[i] = new Brick(
            SCREEN_EDGE_OFFSET + (i * (FIXED_BRICK_WIDTH + GAP_BETWEEN_BRICKS)), 
            100,
            FIXED_BRICK_WIDTH,
            FIXED_BRICK_HEIGHT
        );
    }
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
    if (ball->position.x - ball->radius <= 0) 
    {
        ball->position.x = ball->radius;
        ball->velocity.x *= -1;
    } 
    else if (ball->position.x + ball->radius >= WINDOW_WIDTH) 
    {
        ball->position.x = WINDOW_WIDTH - ball->radius;
        ball->velocity.x *= -1;
    }

    if (ball->position.y - ball->radius <= 0) 
    {
        ball->position.y = ball->radius;
        ball->velocity.y *= -1;
    } 
    else if (ball->position.y + ball->radius >= WINDOW_HEIGHT) 
    {
        ball->position.y = WINDOW_HEIGHT - ball->radius;
        ball->velocity.y *= -1;
    }

    // Screen Borders for Paddle
    if (paddle->position.x < 0) 
    {
        paddle->position.x = 0;
    } 
    else if (paddle->position.x + paddle->width > WINDOW_WIDTH) 
    {
        paddle->position.x = WINDOW_WIDTH - paddle->width;
    }

    // BALL AND PADDLE COLLISIONS // TODO: left, right and middle areas of the paddle should behave differently
    if (ball->position.y + ball->radius > paddle->position.y && 
        ball->position.x + ball->radius < paddle->position.x + paddle->width &&
        ball->position.x - ball->radius > paddle->position.x) 
    {
        ball->velocity.y *= -1; // Only change y direction if ball hits the top of the paddle
    }
    else if (ball->position.x + ball->radius > paddle->position.x &&
        ball->position.y + ball->radius > paddle->position.y &&
        ball->position.x - ball->radius < paddle->position.x + paddle->width &&
        ball->position.y - ball->radius < paddle->position.y + paddle->height)
    {
        ball->velocity.x *= -1;
        ball->velocity.y *= -1;
    }

    // BALL AND BRICK COLLISIONS
    for (int i = 0; i < NUMBER_OF_BRICKS; i++)
    {
        if (!bricks[i]->isActive) continue; // Don't check for collision if it is not active

        if (ball->position.x + ball->radius > bricks[i]->position.x &&
            ball->position.y + ball->radius > bricks[i]->position.y &&
            ball->position.x - ball->radius < bricks[i]->position.x + bricks[i]->width &&
            ball->position.y - ball->radius < bricks[i]->position.y + bricks[i]->height)
        {
            ball->velocity.y *= -1;
            bricks[i]->isActive = false; // Don't render and don't check for collision if it is not active
        }
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw ball
    ball->DrawBall(renderer);
    //filledCircleColor(renderer, ball->position.x, ball->position.y, ball->radius, 0xFFFFFFFF);
    
    // Draw paddle
    SDL_Rect fillRectPaddle = { 
        paddle->position.x, 
        paddle->position.y, 
        paddle->width, 
        paddle->height
    };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);		
	SDL_RenderFillRect(renderer, &fillRectPaddle);

    //Draw bricks
    for (int i = 0; i < NUMBER_OF_BRICKS; i++)
    {
        if (!bricks[i]->isActive) continue; // Don't render if it is not active

        SDL_Rect fillRectPaddle = { 
            bricks[i]->position.x, 
            bricks[i]->position.y, 
            bricks[i]->width, 
            bricks[i]->height
        };
	    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);		
	    SDL_RenderFillRect(renderer, &fillRectPaddle);
    }

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    delete ball;
    delete paddle;

    for (int i = 0; i < NUMBER_OF_BRICKS; i++)
    {
        delete bricks[i];
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
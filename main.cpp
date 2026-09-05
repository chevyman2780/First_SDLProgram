#include <iostream>
#include <SDL2/SDL.h>

int buildWindow(int argc, char** args, SDL_Window* &window, SDL_Renderer* &renderer, int width, int height, int rgb1, int rgb2, int rgb3) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Could not start program" << std::endl;
        exit(-1);
    }

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cout << "Failure to make window" << std::endl;

        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, rgb1, rgb2, rgb3, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return 0;
}

void frameLoop(float& dt) {
    Uint32 last_time = SDL_GetTicks();

    Uint32 current_time = SDL_GetTicks();

    // Delta time in seconds
    dt = (current_time - last_time) / 1000.00f;
    last_time = current_time;
}

int main(int argc, char** args) {
    float dt;

    // Window pointers
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    buildWindow(argc, args, window, renderer, 1280, 720, 255, 255, 255);


    // Main running event
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        frameLoop(dt);
    }

    // Destroy window 
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}
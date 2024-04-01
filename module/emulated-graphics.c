#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Function to increase the intensity of a color component
Uint8 increaseIntensity(Uint8 component) {
    // Increase the intensity by a larger fixed amount
    if (component < 255) {
        return component + 5; // Increase by 5 instead of 1
    }
    return 255;  // Ensure the component doesn't exceed 255
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    // Query the screen size
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    int screenWidth = dm.w;
    int screenHeight = dm.h;

    SDL_Window* window = SDL_CreateWindow("Color Emulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    int quit = 0;

    // Initial color values
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Increase intensity of each color component more aggressively
        r = increaseIntensity(r);
        g = increaseIntensity(g);
        b = increaseIntensity(b);

        // Set background color
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Add delay to slow down the color change
        SDL_Delay(50); // Increase delay for slower color change
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

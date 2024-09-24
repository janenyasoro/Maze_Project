#include "rain.h"
#include <stdlib.h>

RainManager* init_rain_manager(int screen_width, int screen_height) {
    RainManager* manager = malloc(sizeof(RainManager));
    if (!manager) return NULL;

    manager->width = screen_width;
    manager->height = screen_height;

    // Initialize raindrops with random positions and speeds
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        manager->raindrops[i].x = rand() % screen_width;
        manager->raindrops[i].y = rand() % screen_height;
        manager->raindrops[i].speed = 5 + rand() % 10;
    }

    return manager;
}

void free_rain_manager(RainManager* manager) {
    if (manager) {
        free(manager);
    }
}

void update_rain(RainManager* manager) {
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        // Move raindrops downwards
        manager->raindrops[i].y += manager->raindrops[i].speed;
        
        // Reset raindrop position if it goes off-screen
        if (manager->raindrops[i].y > manager->height) {
            manager->raindrops[i].y = 0;
            manager->raindrops[i].x = rand() % manager->width;
        }
    }
}

void draw_rain(SDL_Renderer* renderer, RainManager* manager) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 100);
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        // Draw each raindrop as a short vertical line
        SDL_RenderDrawLine(renderer, 
                           manager->raindrops[i].x, 
                           manager->raindrops[i].y, 
                           manager->raindrops[i].x, 
                           manager->raindrops[i].y + 5);
    }
}

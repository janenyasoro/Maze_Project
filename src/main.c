#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "raycaster.h"
#include "textures.h"
#include "player.h"
#include "map.h"
#include "enemy.h"
#include "weapon.h"
#include "rain.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Player player = {1.5, 1.5, 1.0, 0.0, 0.0, 0.066, 0};
    Map* map = NULL;
    TextureManager* texture_manager = NULL;
    EnemyManager* enemy_manager = NULL;
    WeaponManager* weapon_manager = NULL;
    RainManager* rain_manager = NULL;
    bool is_raining = false;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Maze Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize texture manager
    texture_manager = init_texture_manager(renderer);
    if (texture_manager == NULL) {
        printf("Failed to initialize texture manager\n");
        return 1;
    }

    // Load map
    map = load_map("assets/map.txt");
    if (map == NULL) {
        printf("Failed to load map\n");
        return 1;
    }

    // Initialize enemy manager
    enemy_manager = init_enemy_manager(map);
    if (enemy_manager == NULL) {
        printf("Failed to initialize enemy manager\n");
        return 1;
    }

    // Initialize weapon manager
    weapon_manager = init_weapon_manager(renderer);
    if (weapon_manager == NULL) {
        printf("Failed to initialize weapon manager\n");
        return 1;
    }

    // Initialize rain manager
    rain_manager = init_rain_manager(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (rain_manager == NULL) {
        printf("Failed to initialize rain manager\n");
        return 1;
    }

    // Main game loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            handle_input(&e, &player, weapon_manager);

            // Toggle rain with 'R' key
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
                is_raining = !is_raining;
            }
        }

        // Update player position
        update_player(&player, map);

        // Update enemies
        update_enemies(enemy_manager, &player, map);

        // Update rain
        if (is_raining) {
            update_rain(rain_manager);
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render walls with lighting effects
        render_walls(renderer, &player, map, texture_manager, is_raining);

        // Render enemies
        draw_enemies(renderer, enemy_manager, &player, map);

        // Render rain
        if (is_raining) {
            draw_rain(renderer, rain_manager);
        }

        // Render weapon
        draw_weapon(renderer, weapon_manager, player.current_weapon);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    free_texture_manager(texture_manager);
    free_map(map);
    free_enemy_manager(enemy_manager);
    free_weapon_manager(weapon_manager);
    free_rain_manager(rain_manager);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

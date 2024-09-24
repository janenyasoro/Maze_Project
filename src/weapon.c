#include "weapon.h"
#include <SDL2/SDL_image.h>

WeaponManager* init_weapon_manager(SDL_Renderer* renderer) {
    WeaponManager* manager = malloc(sizeof(WeaponManager));
    if (!manager) return NULL;

    const char* weapon_files[] = {
        "assets/weapon1.png",
        "assets/weapon2.png"
    };

    // Load weapon textures and initialize weapon properties
    for (int i = 0; i < MAX_WEAPONS; i++) {
        SDL_Surface* surface = IMG_Load(weapon_files[i]);
        if (!surface) {
            printf("Failed to load weapon texture: %s\n", weapon_files[i]);
            free_weapon_manager(manager);
            return NULL;
        }
        manager->weapons[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!manager->weapons[i].texture) {
            printf("Failed to create weapon texture: %s\n", weapon_files[i]);
            free_weapon_manager(manager);
            return NULL;
        }
        manager->weapons[i].ammo = 100;
        manager->weapons[i].damage = 10 * (i + 1);
    }

    return manager;
}

void free_weapon_manager(WeaponManager* manager) {
    if (manager) {
        for (int i = 0; i < MAX_WEAPONS; i++) {
            if (manager->weapons[i].texture) {
                SDL_DestroyTexture(manager->weapons[i].texture);
            }
        }
        free(manager);
    }
}

void fire_weapon(WeaponManager* manager, int weapon_id) {
    if (weapon_id >= 0 && weapon_id < MAX_WEAPONS) {
        if (manager->weapons[weapon_id].ammo > 0) {
            manager->weapons[weapon_id].ammo--;
            printf("Fired weapon %d. Ammo left: %d\n", weapon_id, manager->weapons[weapon_id].ammo);
        } else {
            printf("Out of ammo for weapon %d\n", weapon_id);
        }
    }
}

void draw_weapon(SDL_Renderer* renderer, WeaponManager* manager, int current_weapon) {
    if (current_weapon >= 0 && current_weapon < MAX_WEAPONS) {
        SDL_Texture* weapon_texture = manager->weapons[current_weapon].texture;
        int texture_width, texture_height;
        SDL_QueryTexture(weapon_texture, NULL, NULL, &texture_width, &texture_height);

        // Calculate weapon position on screen
        SDL_Rect dest_rect = {
            SCREEN_WIDTH / 2 - texture_width / 4,
            SCREEN_HEIGHT - texture_height / 2,
            texture_width / 2,
            texture_height / 2
        };
        SDL_RenderCopy(renderer, weapon_texture, NULL, &dest_rect);
    }
}

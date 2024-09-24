#include "textures.h"
#include <SDL2/SDL_image.h>

// Initialize the texture manager
TextureManager* init_texture_manager(SDL_Renderer* renderer)
{
    TextureManager* manager = malloc(sizeof(TextureManager));
    if (!manager)
        return NULL;

    // List of texture files
    const char* texture_files[] = {
        "assets/wall1.png",
        "assets/wall2.png",
        "assets/ground.png",
        "assets/ceiling.png",
        "assets/weapon.png",
        "assets/enemy.png"
    };

    // Load textures
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        if (i < sizeof(texture_files) / sizeof(texture_files[0]))
        {
            SDL_Surface* surface = IMG_Load(texture_files[i]);
            if (!surface)
            {
                printf("Failed to load texture: %s\n", texture_files[i]);
                free_texture_manager(manager);
                return NULL;
            }
            manager->textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            if (!manager->textures[i])
            {
                printf("Failed to create texture: %s\n", texture_files[i]);
                free_texture_manager(manager);
                return NULL;
            }
        }
        else
        {
            manager->textures[i] = NULL;
        }
    }

    return manager;
}

// Free the texture manager and its resources
void free_texture_manager(TextureManager* manager)
{
    if (manager)
    {
        for (int i = 0; i < MAX_TEXTURES; i++)
        {
            if (manager->textures[i])
                SDL_DestroyTexture(manager->textures[i]);
        }
        free(manager);
    }
}

// Get a texture by its ID
SDL_Texture* get_texture(TextureManager* manager, int texture_id)
{
    if (texture_id >= 0 && texture_id < MAX_TEXTURES)
        return manager->textures[texture_id];
    return NULL;
}

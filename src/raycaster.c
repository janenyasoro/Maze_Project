#include "raycaster.h"
#include <math.h>

#define FOV 60
#define HALF_FOV 30
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void render_walls(SDL_Renderer* renderer, Player* player, Map* map, TextureManager* texture_manager, bool is_raining) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate ray angle
        double ray_angle = (player->angle - HALF_FOV) + ((double)x / SCREEN_WIDTH) * FOV;
        double ray_cos = cos(ray_angle * M_PI / 180);
        double ray_sin = sin(ray_angle * M_PI / 180);

        // Initialize ray position and properties
        double ray_x = player->x;
        double ray_y = player->y;
        double distance = 0;
        int hit_wall = 0;
        int texture_id = 0;

        // Cast ray until it hits a wall or reaches maximum distance
        while (!hit_wall && distance < 20) {
            distance += 0.1;
            ray_x = player->x + distance * ray_cos;
            ray_y = player->y + distance * ray_sin;

            // Check if ray is out of bounds
            if (ray_x < 0 || ray_x >= map->width || ray_y < 0 || ray_y >= map->height) {
                hit_wall = 1;
                distance = 20;
            } else if (map->data[(int)ray_y][(int)ray_x] > 0) {
                // Ray hit a wall
                hit_wall = 1;
                texture_id = map->data[(int)ray_y][(int)ray_x];
            }
        }
        
        // Calculate wall height and drawing boundaries
        int wall_height = (int)(SCREEN_HEIGHT / (distance * cos((ray_angle - player->angle) * M_PI / 180)));
        int draw_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = wall_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

        // Get wall texture
        SDL_Texture* wall_texture = get_texture(texture_manager, texture_id);
        int texture_width, texture_height;
        SDL_QueryTexture(wall_texture, NULL, NULL, &texture_width, &texture_height);
        
        // Calculate texture coordinates
        double wall_x;
        if (fabs(ray_sin) > fabs(ray_cos)) {
            wall_x = player->x + ((ray_y - player->y) / ray_sin) * ray_cos;
        } else {
            wall_x = player->y + ((ray_x - player->x) / ray_cos) * ray_sin;
        }
        wall_x -= floor(wall_x);

        int texture_x = (int)(wall_x * texture_width);
        if ((ray_cos > 0 && ray_sin < 0) || (ray_cos < 0 && ray_sin > 0)) texture_x = texture_width - texture_x - 1;

        // Calculate texture step and position
        double step = 1.0 * texture_height / wall_height;
        double texture_pos = (draw_start - SCREEN_HEIGHT / 2 + wall_height / 2) * step;

        // Set up source and destination rectangles for rendering
        SDL_Rect src_rect = {texture_x, 0, 1, texture_height};
        SDL_Rect dest_rect = {x, draw_start, 1, draw_end - draw_start};

        // Apply lighting effects
        Uint8 r, g, b;
        SDL_GetTextureColorMod(wall_texture, &r, &g, &b);
        
        // Darken walls based on distance
        double darkness_factor = 1.0 - (distance / 20.0);
        r = (Uint8)(r * darkness_factor);
        g = (Uint8)(g * darkness_factor);
        b = (Uint8)(b * darkness_factor);

        // Apply rain effect (slightly blue tint)
        if (is_raining) {
            b = (Uint8)fmin(255, b * 1.2);
        }

        SDL_SetTextureColorMod(wall_texture, r, g, b);
        SDL_RenderCopy(renderer, wall_texture, &src_rect, &dest_rect);
    }
}

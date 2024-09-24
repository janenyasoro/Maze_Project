#include "player.h"
#include <math.h>

void handle_input(SDL_Event* e, Player* player, WeaponManager* weapon_manager) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_UP:
                player->x += player->dir_x * player->move_speed;
                player->y += player->dir_y * player->move_speed;
                break;
            case SDLK_DOWN:
                player->x -= player->dir_x * player->move_speed;
                player->y -= player->dir_y * player->move_speed;
                break;
            case SDLK_LEFT:
                player->angle -= player->rot_speed;
                if (player->angle < 0) player->angle += 360;
                player->dir_x = cos(player->angle * M_PI / 180);
                player->dir_y = sin(player->angle * M_PI / 180);
                player->plane_x = -player->dir_y * 0.66;
                player->plane_y = player->dir_x * 0.66;
                break;
            case SDLK_RIGHT:
                player->angle += player->rot_speed;
                if (player->angle >= 360) player->angle -= 360;
                player->dir_x = cos(player->angle * M_PI / 180);
                player->dir_y = sin(player->angle * M_PI / 180);
                player->plane_x = -player->dir_y * 0.66;
                player->plane_y = player->dir_x * 0.66;
                break;
            case SDLK_SPACE:
                fire_weapon(weapon_manager, player->current_weapon);
                break;
            case SDLK_1:
                player->current_weapon = 0;
                break;
            case SDLK_2:
                player->current_weapon = 1;
                break;
        }
    }
}

void update_player(Player* player, Map* map) {
    int map_x = (int)player->x;
    int map_y = (int)player->y;

    if (map->data[map_y][map_x] > 0) {
        player->x -= player->dir_x * player->move_speed;
        player->y -= player->dir_y * player->move_speed;
    }
}

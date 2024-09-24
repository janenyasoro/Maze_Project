#include "enemy.h"
#include <stdlib.h>
#include <math.h>

// Initialize the enemy manager
EnemyManager* init_enemy_manager(Map* map) {
    EnemyManager* manager = malloc(sizeof(EnemyManager));
    if (!manager) return NULL;

    manager->count = 0;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        int x, y;
        do {
            x = rand() % map->width;
            y = rand() % map->height;
        } while (map->data[y][x] != 0);

        manager->enemies[manager->count].x = x + 0.5;
        manager->enemies[manager->count].y = y + 0.5;
        manager->enemies[manager->count].texture_id = 5; // Assuming enemy texture ID is 5
        manager->enemies[manager->count].health = 100;
        manager->count++;
    }

    return manager;
}

void free_enemy_manager(EnemyManager* manager) {
    if (manager) {
        free(manager);
    }
}

void update_enemies(EnemyManager* manager, Player* player, Map* map) {
    for (int i = 0; i < manager->count; i++) {
        Enemy* enemy = &manager->enemies[i];
        double dx = player->x - enemy->x;
        double dy = player->y - enemy->y;
        double distance = sqrt(dx * dx + dy * dy);

        if (distance < 5) {
            double move_speed = 0.03;
            double new_x = enemy->x + (dx / distance) * move_speed;
            double new_y = enemy->y + (dy / distance) * move_speed;

            if (map->data[(int)new_y][(int)new_x] == 0) {
                enemy->x = new_x;
                enemy->y = new_y;
            }
        }
    }
}

void draw_enemies(SDL_Renderer* renderer, EnemyManager* manager, Player* player, Map* map) {
    for (int i = 0; i < manager->count; i++) {
        Enemy* enemy = &manager->enemies[i];
        double dx = enemy->x - player->x;
        double dy = enemy->y - player->y;
        double distance = sqrt(dx * dx + dy * dy);

        double angle = atan2(dy, dx) - player->angle * M_PI / 180;
        if (angle < -M_PI) angle += 2 * M_PI;
        if (angle > M_PI) angle -= 2 * M_PI;

        if (fabs(angle) < FOV / 2 * M_PI / 180) {
            double sprite_size = SCREEN_HEIGHT / distance;
            double sprite_x = (angle / (FOV * M_PI / 180) + 0.5) * SCREEN_WIDTH - sprite_size / 2;
            double sprite_y = SCREEN_HEIGHT / 2 - sprite_size / 2;

            SDL_Rect dest_rect = {sprite_x, sprite_y, sprite_size, sprite_size};
            SDL_RenderCopy(renderer, get_texture(texture_manager, enemy->texture_id), NULL, &dest_rect);
        }
    }
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** bullet related header
*/

#ifndef BULLET_H_
    #define BULLET_H_

    #include <stdbool.h>
    #include <SFML/System/Vector2.h>
    #include "my_bgs.h"
    #include "defender_game_data.h"

struct bullet_s {
    sfVector2f direction;
    sfVector2f initial_position;
    int is_fly;
    int dmg;
};
typedef struct bullet_s bullet_t;

void update_bullet(object_t *obj, scene_t *scene, window_t *win, float dtime);

void spawn_bullet(scene_t *scene, sfVector2f vector[2],
    tower_data_t *tower_data, window_t *win);

double get_coef(sfFloatRect intersection, sfSprite *tower);

int check_if_need_remove(bullet_t *bullet, object_t *obj);

void create_damage_enn_info(scene_t *scene, sfVector2f pos, int nb_dmg);

#endif

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** bullet related header
*/

#ifndef BULLET_H_
    #define BULLET_H

    #include <stdbool.h>
    #include <SFML/System/Vector2.h>
    #include "my_bgs.h"

struct bullet_s {
    sfVector2f direction;
    bool is_fly;
};
typedef struct bullet_s bullet_t;

void update_bullet(object_t *obj, scene_t *scene, window_t *win, float dtime);

void spawn_bullet(scene_t *scene, sfVector2f initial_position,
        sfVector2f direction, bool is_fly);

#endif

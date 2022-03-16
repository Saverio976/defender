/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create bullet
*/

#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "defender_bullet.h"
#include "defender_game_data.h"
#include "my_bgs.h"

void spawn_bullet(scene_t *scene, sfVector2f initial_position,
        sfVector2f direction, tower_data_t *tower_data)
{
    object_t *obj = NULL;
    bullet_t *bullet = NULL;

    bullet = malloc(sizeof(bullet_t));
    if (bullet == NULL || scene == NULL) {
        return;
    }
    bullet->direction = direction;
    bullet->is_fly = tower_data->fly;
    bullet->dmg = tower_data->damage;
    obj = create_object(update_bullet, NULL, scene);
    if (obj == NULL) {
        free(bullet);
        return;
    }
    object_set_sprite(obj, "assets/image/menu/level/octo.png",
            (sfIntRect) {-1, -1, -1, -1}, initial_position);
    object_add_components(obj, bullet, "DIRECTION BULLET", NULL);
    list_add_to_end(scene->displayables, obj);
    list_add_to_end(scene->updates, obj);
}

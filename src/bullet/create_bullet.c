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

static bullet_t *create_bullet(sfVector2f direction, tower_data_t *tower_data)
{
    bullet_t *bullet = NULL;

    if (tower_data == NULL) {
        return (NULL);
    }
    bullet = malloc(sizeof(bullet_t));
    if (bullet == NULL) {
        return (NULL);
    }
    bullet->direction = direction;
    bullet->is_fly = tower_data->fly;
    bullet->dmg = tower_data->damage;
    return (bullet);
}

static void set_sprite_bullet(object_t *obj, tower_data_t *tower_data,
        sfVector2f initial_position, scene_t *scene)
{
    object_set_sprite(obj, tower_data->sprite_bullet,
        tower_data->sprite_int_rect, initial_position);
    list_add_to_end(scene->displayables, obj);
    list_add_to_end(scene->updates, obj);
}

void spawn_bullet(scene_t *scene, sfVector2f initial_position,
        sfVector2f direction, tower_data_t *tower_data)
{
    object_t *obj = NULL;
    bullet_t *bullet = NULL;

    bullet = create_bullet(direction, tower_data);
    if (bullet == NULL) {
        return;
    }
    obj = create_object(update_bullet, NULL, scene);
    if (obj == NULL) {
        free(bullet);
        return;
    }
    bullet->initial_position = initial_position;
    object_add_components(obj, bullet, "DIRECTION BULLET", free);
    set_sprite_bullet(obj, tower_data, initial_position, scene);
}

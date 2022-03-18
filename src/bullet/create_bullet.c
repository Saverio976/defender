/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create bullet
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundStatus.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "my_bgs.h"
#include "defender_bullet.h"
#include "defender_game_data.h"
#include "defender_bullet.h"

static void set_rotation_sprite_bullet(object_t *obj, sfVector2f direction)
{
    double angle = 0;
    sfFloatRect rect = {direction.x - 1, direction.y - 1, 3, 3};

    if (obj == NULL || obj->type != SPRITE) {
        return;
    }
    angle = get_coef(rect, obj->drawable.sprite) - 90;
    sfSprite_setRotation(obj->drawable.sprite, angle);
}

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

static void play_sound(tower_data_t *tower, game_data_t *game_data)
{
    sfSoundStatus status = {0};

    if (tower == NULL || tower->sound == NULL || game_data == NULL ||
        game_data->sound_effect == false) {
        return;
    }
    status = sfSound_getStatus(tower->sound);
    if (status == sfPlaying) {
        sfSound_stop(tower->sound);
    }
    sfSound_play(tower->sound);
}

void spawn_bullet(scene_t *scene, sfVector2f vector[2],
    tower_data_t *tower_data, window_t *win)
{
    object_t *obj = NULL;
    bullet_t *bullet = NULL;

    bullet = create_bullet(vector[1], tower_data);
    if (bullet == NULL) {
        return;
    }
    obj = create_object(update_bullet, NULL, scene);
    if (obj == NULL) {
        free(bullet);
        return;
    }
    bullet->initial_position = vector[0];
    object_add_components(obj, bullet, "DIRECTION BULLET", free);
    set_sprite_bullet(obj, tower_data, vector[0], scene);
    play_sound(tower_data, dico_t_get_value(win->components, GAME_DATA));
    set_rotation_sprite_bullet(obj, vector[1]);
}

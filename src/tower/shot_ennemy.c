/*
** EPITECH PROJECT, 2022
** defender
** File description:
** shot ennemy
*/

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <math.h>
#include "defender_bullet.h"
#include "defender_game_data.h"
#include "list.h"
#include "my_bgs.h"
#include "my_dico.h"

static float pi = 3.1415926535;

static float get_coef(sfFloatRect intersection, sfFloatRect tower)
{
    float y1 = 0;
    float y2 = 0;
    float x1 = 0;
    float x2 = 0;
    double angle = 0;

    x1 = tower.left + tower.width / 2;
    y1 = tower.height + tower.height / 2;
    x2 = intersection.left + intersection.width / 2;
    y2 = intersection.top + intersection.height / 2;
    angle = atan2(y2 - y1, x2 - x1) * 180 / pi;
    return (angle);
}

void update_bullet(object_t *obj, scene_t *scene, window_t *win, float dtime)
{
    bullet_t *bullet = NULL;
    float new_x =  0;
    float new_y = 0;
    float curr_x = 0;
    float curr_y = 0;

    if (obj == NULL) {
        return;
    }
    bullet = dico_t_get_value(obj->components, "DIRECTION BULLET");
    if (bullet == NULL) {
        return;
    }
    curr_x = obj->bigdata.sprite_bigdata.pos.x;
    curr_y = obj->bigdata.sprite_bigdata.pos.y;
    new_x = curr_x + (dtime * (bullet->direction.x - curr_x));
    new_y = curr_y + (dtime * (bullet->direction.y - curr_y));
    obj->bigdata.sprite_bigdata.pos.x = new_x;
    obj->bigdata.sprite_bigdata.pos.y = new_y;
}

void spawn_bullet(scene_t *scene, sfVector2f initial_position,
        sfVector2f direction, bool is_fly)
{
    object_t *obj = NULL;
    bullet_t *bullet = NULL;

    bullet = malloc(sizeof(bullet_t));
    if (bullet == NULL || scene == NULL) {
        return;
    }
    bullet->direction = direction;
    bullet->is_fly = is_fly;
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

void shot_ennemy(sfFloatRect intersection, object_t *tower,
        tower_data_t *tower_data, scene_t *scene)
{
    float angle = 0;

    if (tower == NULL) {
        return;
    }
    angle = get_coef(intersection,
            sfSprite_getGlobalBounds(tower->drawable.sprite));
    sfSprite_setRotation(tower->drawable.sprite, angle + 90);
    if (tower_data->dtime > tower_data->cadence) {
        spawn_bullet(scene, sfSprite_getPosition(tower->drawable.sprite),
                (sfVector2f) {intersection.left + intersection.width / 2,
                intersection.top + intersection.height / 2}, tower_data->fly);
        tower_data->dtime = 0;
    }
}

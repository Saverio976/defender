/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update bullet
*/

#include "my_bgs.h"
#include "defender_bullet.h"

void update_bullet(object_t *obj, scene_t *scene, window_t *win, float dtime)
{
    bullet_t *bullet = NULL;
    float new_x = 0;
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

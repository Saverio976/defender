/*
** EPITECH PROJECT, 2022
** defender
** File description:
** shot ennemy
*/

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <math.h>
#include "defender_bullet.h"
#include "defender_ennemy.h"
#include "defender_game_data.h"
#include "list.h"
#include "my_bgs.h"
#include "my_dico.h"

static float pi = 3.1415926535;

double get_coef(sfFloatRect intersection, sfSprite *tower)
{
    float y1 = 0;
    float y2 = 0;
    float x1 = 0;
    float x2 = 0;
    double angle = 0;

    x1 = sfSprite_getPosition(tower).x;
    y1 = sfSprite_getPosition(tower).y;
    x2 = intersection.left + intersection.width / 2;
    y2 = intersection.top + intersection.height / 2;
    angle = atan2(y2 - y1, x2 - x1) * 180 / pi;
    return (angle + 90);
}

static void set_rotation(object_t *obj_enn, object_t *obj_tower)
{
    double angle = 0;

    angle = get_coef(sfSprite_getGlobalBounds(obj_enn->drawable.sprite),
            obj_tower->drawable.sprite);
    sfSprite_setRotation(obj_tower->drawable.sprite, angle);
}

void shot_ennemy(object_t *ennemy_obj, object_t *tower,
        tower_data_t *tower_data, scene_t *scene)
{
    ennemy_t *enemy = NULL;

    if (tower == NULL || tower_data == NULL || scene == NULL ||
            ennemy_obj == NULL) {
        return;
    }
    enemy = dico_t_get_value(ennemy_obj->components, OBJ_COMP_ENNSTRUCT);
    if (enemy == NULL) {
        return;
    }
    set_rotation(ennemy_obj, tower);
    if (tower_data->dtime > tower_data->cadence &&
            enemy->is_fly == tower_data->fly) {
        spawn_bullet(scene, sfSprite_getPosition(tower->drawable.sprite),
            sfSprite_getPosition(ennemy_obj->drawable.sprite), tower_data);
        tower_data->dtime = 0;
    }
}

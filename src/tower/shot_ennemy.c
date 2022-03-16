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

static double get_coef(sfFloatRect intersection, sfSprite *tower)
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

void shot_ennemy(sfFloatRect intersection, object_t *tower,
        tower_data_t *tower_data, scene_t *scene)
{
    double angle = 0;

    if (tower == NULL) {
        return;
    }
    angle = get_coef(intersection, tower->drawable.sprite);
    sfSprite_setRotation(tower->drawable.sprite, angle);
    if (tower_data->dtime > tower_data->cadence) {
        spawn_bullet(scene, sfSprite_getPosition(tower->drawable.sprite),
                (sfVector2f) {intersection.left + intersection.width / 2,
                intersection.top + intersection.height / 2}, tower_data);
        tower_data->dtime = 0;
    }
}

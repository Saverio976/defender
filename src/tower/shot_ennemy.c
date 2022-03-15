/*
** EPITECH PROJECT, 2022
** defender
** File description:
** shot ennemy
*/

#include <math.h>
#include "defender_game_data.h"

static float pi = 3.1415926535;

static float get_coef(sfFloatRect intersection, sfFloatRect tower)
{
    sfVector2f intersec_pos = {intersection.left + (intersection.width / 2),
        intersection.top + (intersection.height / 2)};
    sfVector2f tower_pos = {tower.left + (tower.width / 2),
        tower.top + (tower.height / 2)};
    float x = intersec_pos.x - tower_pos.x;
    float y = intersec_pos.y - tower_pos.y;

    return y / x;
}

void shot_ennemy(sfFloatRect intersection, object_t *tower)
{
    float coef = get_coef(intersection,
        sfSprite_getGlobalBounds(tower->drawable.sprite));

    sfSprite_setRotation(tower->drawable.sprite, (atan(coef) * 250 / pi));
    return;
}

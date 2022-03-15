/*
** EPITECH PROJECT, 2022
** defender
** File description:
** shot ennemy
*/

#include <SFML/Graphics/Sprite.h>
#include <math.h>
#include <SFML/Graphics.h>
#include "defender_game_data.h"

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

void shot_ennemy(sfFloatRect intersection, object_t *tower)
{
    float angle = 0;

    if (tower == NULL) {
        return;
    }
    angle = get_coef(intersection,
            sfSprite_getGlobalBounds(tower->drawable.sprite));
    sfSprite_setRotation(tower->drawable.sprite, angle + 90);
    return;
}

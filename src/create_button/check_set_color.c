/*
** EPITECH PROJECT, 2022
** defender
** File description:
** check set color
*/

#include "defender.h"

void check_set_color(object_t *object, dico_t *dico)
{
    int *color = get_any_int_array(dico_t_get_any(dico, "color"));

    if (color == NULL) {
        return;
    }
    if (object->type == SPRITE) {
        sfSprite_setColor(object->drawable.sprite, sfColor_fromRGB(color[0],
            color[1], color[2]));
    } else if (object->type == TEXT) {
        sfText_setColor(object->drawable.text, sfColor_fromRGB(color[0],
            color[1], color[2]));
    }
}

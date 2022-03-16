/*
** EPITECH PROJECT, 2022
** defender
** File description:
** fill  data bullet
*/

#include "defender_game_data.h"
#include "my_strings.h"

object_t *fill_data_bullet(object_t *obj, dico_t *dico,
        tower_data_t *tower_data)
{
    any_t *rect = dico_t_get_any(dico, "rect sprite bullet");
    any_t *rect_a = get_from_any(rect, "a", 0);
    any_t *rect_b = get_from_any(rect, "a", 1);
    any_t *rect_c = get_from_any(rect, "a", 2);
    any_t *rect_d = get_from_any(rect, "a", 3);
    any_t *sprite = dico_t_get_any(dico, "path sprite bullet");

    tower_data->sprite_int_rect = (sfIntRect) {0, 0, 100, 100};
    tower_data->sprite_bullet = my_strdup("assets/image/bullet/fireshot.png");
    if (tower_data == NULL || dico == NULL || rect == NULL || rect_a == NULL ||
            rect_b == NULL || rect_c == NULL || rect_d == NULL ||
            sprite == NULL) {
        return (obj);
    }
    tower_data->sprite_int_rect = (sfIntRect) {rect_a->value.i,
        rect_b->value.i, rect_c->value.i, rect_d->value.i};
    tower_data->sprite_bullet = my_strdup(sprite->value.str);
    return (obj);
}

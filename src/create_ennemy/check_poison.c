/*
** EPITECH PROJECT, 2022
** defender
** File description:
** check poison
*/

#include "defender_ennemy.h"
#include "defender_game_data.h"

int check_poison(object_t *ennemy, scene_t *scene, ennemy_t *enn)
{
    int ret = 0;
    list_ptr_t *list = dico_t_get_value(scene->components, POISON_LIST);
    list_t *elem = NULL;
    sfVector2f pos;
    poison_t *poison = NULL;

    if (list == NULL || ennemy == NULL || enn->is_fly == true) {
        return 0;
    }
    elem = list->start;
    for (int i = 0; i < list->len; i++, elem = elem->next) {
        poison = elem->var;
        pos = sfCircleShape_getPosition(poison->scope);
        if (check_circle_col(ennemy, pos, poison->scope_rad) == true) {
            ret += 1;
        }
    }
    return ret;
}

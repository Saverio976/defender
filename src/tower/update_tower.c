/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update tower
*/

#include "defender_game_data.h"

void update_tower(object_t *obj, scene_t *scene, window_t *win, float time)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);
    list_ptr_t *ennemy_list = dico_t_get_value(scene->components,
        "ennemy list");

    if (tower_data == NULL || ennemy_list == NULL) {
        return;
    }
    return;
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** scope event
*/

#include "defender_game_data.h"

void display_scope(object_t *obj, __attribute__((unused)) scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);

    if (tower_data == NULL || tower_data->scope == NULL) {
        return;
    }
    if (tower_data->scope_display == false) {
        tower_data->scope_display = true;
    }
}

void hide_scope(object_t *obj, __attribute__((unused)) scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);

    if (tower_data == NULL || tower_data->scope == NULL) {
        return;
    }
    if (tower_data->scope_display == true) {
        tower_data->scope_display = false;
    }
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** scope event
*/

#include "defender_game_data.h"

void display_scope(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);
    list_t *elem = NULL;

    if (tower_data == NULL || tower_data->scope == NULL) {
        return;
    }
    elem = tower_data->scope->start;
    check_open_elem(scene, win, obj);
    if (((object_t *) elem->var)->is_visible == false) {
        for (int i = 0; i < tower_data->scope->len; i++, elem = elem->next) {
            ((object_t *) elem->var)->is_visible = true;
        }
    } else {
        hide_scope(obj, scene, win, evt);
    }
}

void hide_scope(object_t *obj, __attribute__((unused)) scene_t *scene,
    window_t *win, __attribute__((unused)) set_event_t *evt)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);
    list_t *elem = NULL;

    if (tower_data == NULL || tower_data->scope == NULL) {
        return;
    }
    elem = tower_data->scope->start;
    if (((object_t *) elem->var)->is_visible == true) {
        for (int i = 0; i < tower_data->scope->len; i++, elem = elem->next) {
            ((object_t *) elem->var)->is_visible = false;
        }
    }
    win->click_prev_call = false;
}

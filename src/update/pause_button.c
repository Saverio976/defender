/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update pause button
*/

#include "defender_game_data.h"

void click_escape_button(__attribute__((unused)) object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    list_ptr_t *pause_obj = dico_t_get_value(scene->components, PAUSE_OBJ);

    if (pause_obj == NULL) {
        return;
    }
    if (((object_t *) pause_obj->start->var)->is_visible == false) {
        check_open_elem(NULL, scene, win, NULL);
        click_pause_button(NULL, scene, NULL, NULL);
    } else {
        check_open_elem(NULL, scene, win, NULL);
    }
}

void click_pause_button(__attribute__((unused)) object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    list_ptr_t *pause_obj = dico_t_get_value(scene->components, PAUSE_OBJ);
    list_t *elem = NULL;

    if (pause_obj == NULL) {
        return;
    }
    elem = pause_obj->start;
    for (int i = 0; i < pause_obj->len; i++, elem = elem->next) {
        if (((object_t *) elem->var)->is_visible == true) {
            ((object_t *) elem->var)->is_visible = false;
            scene->pause = false;
        } else {
            ((object_t *) elem->var)->is_visible = true;
            scene->pause = true;
        }
    }
}

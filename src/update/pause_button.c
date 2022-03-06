/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update pause button
*/

#include "defender_game_data.h"

void click_pause_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt)
{
    list_ptr_t *shop_obj = dico_t_get_value(scene->components, PAUSE_OBJ);
    list_t *elem = NULL;

    if (shop_obj == NULL) {
        return;
    }
    elem = shop_obj->start;
    for (int i = 0; i < shop_obj->len; i++, elem = elem->next) {
        if (((object_t *) elem->var)->is_visible == true) {
            ((object_t *) elem->var)->is_visible = false;
        } else {
            ((object_t *) elem->var)->is_visible = true;
        }
    }
}

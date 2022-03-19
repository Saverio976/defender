/*
** EPITECH PROJECT, 2022
** defender
** File description:
** shop update
*/

#include "my_bgs.h"
#include "my_bgs_components.h"
#include "defender_game_data.h"
#include "my_puts.h"

void click_shop_button(__attribute__((unused)) object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    list_ptr_t *shop_obj = dico_t_get_value(scene->components, SHOP_OBJ);
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

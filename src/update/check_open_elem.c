/*
** EPITECH PROJECT, 2022
** defender
** File description:
** check open elem
*/

#include "defender_game_data.h"

static void check_scope(object_t *obj, object_t *cur_tower, scene_t *scene,
    window_t *win)
{
    tower_data_t *tower_data =
        dico_t_get_value(cur_tower->components, TOWER_DATA);

    if (tower_data == NULL ||
        ((object_t *) tower_data->scope->start->var)->is_visible == false) {
        return;
    }
    if ((obj != NULL && cur_tower != obj) || obj == NULL) {
        hide_scope(cur_tower, scene, win, NULL);
    }
}

void check_open_elem(scene_t *scene, window_t *win, object_t *obj)
{
    list_ptr_t *pause_obj = dico_t_get_value(scene->components, PAUSE_OBJ);
    list_ptr_t *shop_obj = dico_t_get_value(scene->components, SHOP_OBJ);
    list_ptr_t *support = dico_t_get_value(scene->components, TOWER_LIST);
    list_t *elem = NULL;

    if (pause_obj != NULL && ((object_t *) pause_obj->start->var)->
        is_visible == true) {
        click_pause_button(NULL, scene, win, NULL);
    } else if (shop_obj != NULL && ((object_t *) shop_obj->start->var)->
        is_visible == true) {
        click_shop_button(NULL, scene, win, NULL);
    }
    if (support == NULL || support->len == 0 || support->start == NULL) {
        return;
    }
    elem = support->start;
    for (int i = 0; i < support->len; i++, elem = elem->next) {
        check_scope(obj, elem->var, scene, win);
    }
}

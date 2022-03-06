/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init side menu
*/

#include "defender.h"
#include "defender_game_data.h"

static void free_list_void(void *data)
{
    list_ptr_t *list = data;

    if (list == NULL) {
        return;
    }
    free_list(list);
}

static void set_shop_back_event(list_t **elem, scene_t *scene)
{
    object_t *back = (*elem)->next->var;

    *elem = (*elem)->next;
    event_add_node(create_event(shop_back_update, false, back, NULL),
        (node_params_t) {sfMouseRight, sfKeyA, MOUSE});
    list_add_to_end(scene->updates, back);
}

int init_side_menu(window_t *win, scene_t *scene)
{
    list_t *elem = NULL;
    list_ptr_t *shop_obj = list_create();

    if (win == NULL || scene == NULL || shop_obj == NULL) {
        return RET_INVALID_INPUT;
    }
    create_button(scene, SIDE_MENU);
    elem = scene->objects->end;
    create_button(scene, SHOP_MENU);
    elem = elem->next;
    //set_shop_back_event(&elem, scene);
    for (; elem != scene->objects->start; elem = elem->next) {
        ((object_t *) elem->var)->is_visible = false;
        list_add_to_end(shop_obj, elem->var);
    }
    scene->components = dico_t_add_data(scene->components, SHOP_OBJ, shop_obj,
        free_list_void);
    if (scene->components == NULL) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

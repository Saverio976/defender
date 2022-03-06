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

static int add_hiden_list(scene_t *scene, list_t **elem, char const key[])
{
    list_ptr_t *list = list_create();

    if (list == NULL) {
        return RET_ERR_MALLOC;
    }
    (*elem) = (*elem)->next;
    for (; (*elem) != scene->objects->start; (*elem) = (*elem)->next) {
        ((object_t *) (*elem)->var)->is_visible = false;
        list_add_to_end(list, (*elem)->var);
    }
    *elem = scene->objects->end;
    scene->components = dico_t_add_data(scene->components, key, list,
        free_list_void);
    if (scene->components == NULL) {
        return RET_ERR_MALLOC;
    }
    printf("******************\n");
    return RET_OK;
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

    if (win == NULL || scene == NULL ||
        create_button(scene, SIDE_MENU) != RET_OK ) {
        return RET_INVALID_INPUT;
    }
    elem = scene->objects->end;
    if (create_button(scene, SHOP_MENU) != RET_OK || add_hiden_list(scene,
        &elem, SHOP_OBJ) != RET_OK || create_button(scene, PAUSE_MENU) != RET_OK
        || add_hiden_list(scene, &elem, PAUSE_OBJ) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    //set_shop_back_event(&elem, scene); mega bug qui a fait crash mon ordi
    return RET_OK;
}

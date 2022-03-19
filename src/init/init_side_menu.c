/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init side menu
*/

#include "defender.h"
#include "defender_game_data.h"

void free_list_void(void *data)
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
    list_t *tmp = *elem;

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
    *elem = tmp;
    return RET_OK;
}

static void set_pause(scene_t *scene, window_t *win)
{
    list_t *elem = scene->objects->end;
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);

    if (create_button(scene, PAUSE_MENU) != RET_OK || game_data == NULL ||
        add_hiden_list(scene, &elem, PAUSE_OBJ) != RET_OK) {
        return;
    } else if (game_data->sound_effect == false) {
        game_data->sound_effect = true;
        click_sound_button(elem->back->var, scene, win, NULL);
    }
    if (game_data->music == false) {
        game_data->music = true;
        click_music_button(elem->back->back->back->var, scene, win, NULL);
    }
}

void add_button_to_scene(dico_t *dico, list_t *elem)
{
    dico = dico_t_add_data(dico, "pause button", elem->var, NULL);
    dico = dico_t_add_data(dico, "shop button", elem->next->var, NULL);
}

int init_side_menu(window_t *win, scene_t *scene)
{
    list_t *elem = scene->objects->end;
    int ennemy_id = 0;

    if (create_button(scene, SIDE_MENU) != RET_OK ) {
        return RET_INVALID_INPUT;
    }
    elem = elem->next->next;
    add_button_to_scene(scene->components, elem);
    event_add_node(create_event(click_escape_button, false, elem->var, NULL),
        (node_params_t) {sfMouseLeft, sfKeyEscape, KEY});
    ennemy_id = scene->displayables->len - 1;
    scene->components = dico_t_add_data(scene->components, ENNEMY_ID,
        (void *) ennemy_id, NULL);
    elem = scene->objects->end;
    if (create_button(scene, SHOP_MENU) != RET_OK || add_hiden_list(scene,
        &elem, SHOP_OBJ) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    set_pause(scene, win);
    return (scene->components != NULL) ? RET_OK : RET_ERR_MALLOC ;
}

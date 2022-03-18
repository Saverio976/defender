/*
** EPITECH PROJECT, 2022
** defender
** File description:
** check open elem
*/

#include "defender_game_data.h"

static void check_scope(__attribute__((unused)) object_t *obj,
    object_t *cur_tower, scene_t *scene, window_t *win)
{
    tower_data_t *tower_data =
        dico_t_get_value(cur_tower->components, TOWER_DATA);
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win->win);
    const sfFloatRect rect =
        sfSprite_getGlobalBounds(cur_tower->drawable.sprite);

    if (tower_data == NULL || tower_data->scope == NULL) {
        return;
    }
    if (sfFloatRect_contains(&rect, mouse.x, mouse.y) == sfTrue &&
        tower_data->scope_display == true) {
        win->click_prev_call = true;
    }
    if (tower_data->scope_display == true) {
        hide_scope(cur_tower, scene, win, NULL);
    }
}

static bool check_shop(list_ptr_t *shop_obj, window_t *win)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win->win);
    const sfFloatRect rect = sfSprite_getGlobalBounds(
        ((object_t *) shop_obj->start->var)->drawable.sprite);

    if (shop_obj != NULL &&
        ((object_t *) shop_obj->start->var)->is_visible == true &&
        sfFloatRect_contains(&rect, mouse.x, mouse.y) == sfFalse) {
        return true;
    }
    return false;
}

static bool check_pause(list_ptr_t *pause_obj, window_t *win)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(win->win);
    const sfFloatRect rect = sfSprite_getGlobalBounds(
        ((object_t *) pause_obj->start->var)->drawable.sprite);

    if (pause_obj != NULL &&
        ((object_t *) pause_obj->start->var)->is_visible == true &&
        sfFloatRect_contains(&rect, mouse.x, mouse.y) == sfFalse) {
        return true;
    }
    return false;
}

void check_open_elem(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    list_ptr_t *pause_obj = dico_t_get_value(scene->components, PAUSE_OBJ);
    list_ptr_t *shop_obj = dico_t_get_value(scene->components, SHOP_OBJ);
    list_ptr_t *support = dico_t_get_value(scene->components, TOWER_LIST);
    list_t *elem = NULL;

    win->click_prev_call = false;
    if (check_pause(pause_obj, win) == true) {
        click_pause_button(NULL, scene, win, NULL);
    } else if (check_shop(shop_obj, win) == true) {
        click_shop_button(NULL, scene, win, NULL);
    }
    if (support == NULL || support->len == 0 || support->start == NULL) {
        return;
    }
    elem = support->start;
    for (int i = 0; i < support->len; i++, elem = elem->next) {
        if (elem->var != NULL) {
            check_scope(obj, elem->var, scene, win);
        }
    }
}

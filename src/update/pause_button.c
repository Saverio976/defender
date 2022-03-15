/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update pause button
*/

#include "defender_game_data.h"

void pause_back_update(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    sfFloatRect rect;
    sfVector2i vector;

    if (obj->type != SPRITE) {
        return;
    }
    rect = sfSprite_getGlobalBounds(obj->drawable.sprite);
    vector = sfMouse_getPositionRenderWindow(win->win);
    sfSprite_setPosition(obj->drawable.sprite, (sfVector2f) {50, 50});
    if (sfFloatRect_contains(&rect, vector.x, vector.y) == sfFalse &&
        obj->is_visible == true) {
        click_pause_button(obj, scene, win, evt);
    }
    win->click_prev_call = false;
}

void click_pause_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt)
{
    list_ptr_t *pause_obj = dico_t_get_value(scene->components, PAUSE_OBJ);
    list_ptr_t *shop_obj = dico_t_get_value(scene->components, SHOP_OBJ);
    list_t *elem = NULL;

    if (pause_obj == NULL || obj->type != SPRITE) {
        return;
    } else if (shop_obj != NULL && ((object_t *) shop_obj->start->var)->
        is_visible == true) {
        click_shop_button(shop_obj->start->var, scene, win, evt);
    }
    elem = pause_obj->start;
    for (int i = 0; i < pause_obj->len; i++, elem = elem->next) {
        if (((object_t *) elem->var)->is_visible == true) {
            ((object_t *) elem->var)->is_visible = false;
            scene->pause = false;
        } else {
            scene->pause = true;;
            ((object_t *) elem->var)->is_visible = true;
        }
    }
}

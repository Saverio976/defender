/*
** EPITECH PROJECT, 2022
** defender
** File description:
** object update
*/

#include <stdbool.h>
#include "my_bgs_components.h"
#include "my_bgs.h"

int check_hover(object_t *object, window_t *win)
{
    sfFloatRect rect;
    sfVector2i vector;

    if (object->type == SPRITE) {
        rect = sfSprite_getGlobalBounds(object->drawable.sprite);
    } else if (object->type == TEXT) {
        rect = sfText_getGlobalBounds(object->drawable.text);
    } else {
        return false;
    }
    vector = sfMouse_getPositionRenderWindow(win->win);
    if (sfFloatRect_contains(&rect, vector.x, vector.y) == sfTrue) {
        return true;
    } else {
        return false;
    }
}

int check_right_click(object_t *object, window_t *win)
{
    if (check_hover(object, win) == 1) {
        if (sfMouse_isButtonPressed(sfMouseRight) == sfTrue) {
            return true;
        } else {
            return false;
        }
    }
    return (false);
}

int check_left_click(object_t *object, window_t *win)
{
    if (check_hover(object, win) == 1) {
        if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue) {
            return false;
        } else {
            return false;
        }
    }
    return (false);
}

void object_update(object_t *object, void *scene_data, window_t *win)
{
    void *data = NULL;

    data = dico_t_get_value(object->components, ON_HOVER_KEY);
    if (data != NULL && check_hover(object, win) == 1) {
        ((on_hover_t *) data)->hover(object, scene_data, win);
    }
    if (data != NULL && check_right_click(object, win) == 1) {
        ((on_right_click_t *) data)->right_click(object, scene_data, win);
    }
    if (data != NULL && check_left_click(object, win) == 1) {
        ((on_left_click_t *) data)->left_click(object, scene_data, win);
    }
}

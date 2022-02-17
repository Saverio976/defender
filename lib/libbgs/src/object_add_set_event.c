/*
** EPITECH PROJECT, 2022
** defender
** File description:
** object add set event
*/

#include <stdlib.h>
#include "my_bgs.h"
#include "my_bgs_components.h"

int object_add_hover_event(object_t *object, void (*hover)(object_t *, void *,
    window_t *win))
{
    on_hover_t *on_hover = NULL;

    if (object->type != TEXT && object->type != SPRITE) {
        return BGS_ERR_INPUT;
    }
    on_hover = malloc(sizeof(on_hover_t));
    if (object == NULL || hover == NULL) {
        return BGS_ERR_INPUT;
    } else if (on_hover == NULL) {
        return BGS_ERR_MALLOC;
    }
    on_hover->hover = hover;
    return object_add_components(object, on_hover, ON_HOVER_KEY, &free);
}

int object_add_right_click_event(object_t *object, void (*right_click)(object_t *,
    void *, window_t *win))
{
    on_right_click_t *on_right = NULL;

    if (object->type != TEXT && object->type != SPRITE) {
        return BGS_ERR_INPUT;
    }
    on_right = malloc(sizeof(on_right_click_t));
    if (object == NULL || right_click == NULL) {
        return BGS_ERR_INPUT;
    } else if (on_right == NULL) {
        return BGS_ERR_MALLOC;
    }
    on_right->right_click = right_click;
    return object_add_components(object, on_right, ON_RIGHT_KEY, &free);
}

int object_add_right_click_event(object_t *object, void (*left_click)(object_t *,
    void *, window_t *win))
{
    on_left_click_t *on_left = NULL;

    if (object->type != TEXT && object->type != SPRITE) {
        return BGS_ERR_INPUT;
    }
    on_left = malloc(sizeof(on_left_click_t));
    if (object == NULL || left_click == NULL) {
        return BGS_ERR_INPUT;
    } else if (on_left == NULL) {
        return BGS_ERR_MALLOC;
    }
    on_left->left_click = left_click;
    return object_add_components(object, on_left, ON_LEFT_KEY, &free);
}

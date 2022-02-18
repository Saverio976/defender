/*
** EPITECH PROJECT, 2022
** defender
** File description:
** object check event
*/

#include "my_bgs.h"
#include "my_strings.h"
#include "my_bgs_components.h"
#include "../include/libbgs_private.h"

static bool check_node(event_node_t *node)
{
    if (node->event_type == MOUSE) {
        if (sfMouse_isButtonPressed(node->event_code.mouse) == sfTrue) {
            return true;
        }
    } else if (node->event_type == KEY) {
        if (sfKeyboard_isKeyPressed(node->event_code.key) == sfTrue) {
            return true;
        }
    }
    return false;
}

static bool check_event_nodes(set_event_t *set_event, object_t *object,
    window_t *win)
{
    bool check = true;
    event_node_t *node = NULL;
    list_t *elem = set_event->list_event->start;

    if (set_event->hover == true && check_hover(object, win) == false) {
        return (false);
    }
    for (int i = 0; i < set_event->list_event->len && check == true;
        i++, elem = elem->next) {
        node = ((event_node_t *) elem->var);
        check = check_node(node);
    }
    return (check);
}

static void check_event(set_event_t *set_event, object_t *object,
    window_t *win, dico_t *scene_components)
{
    bool check = true;

    if (set_event == NULL || set_event->list_event == NULL) {
        return;
    }
    check = check_event_nodes(set_event, object, win);
    if (check == true) {
        set_event->on(object, scene_components, win);
        set_event->prev_call = true;
    } else if (set_event->prev_call == true && check == false) {
        set_event->off(object, scene_components, win);
        set_event->prev_call = false;
    }
}

void object_check_event(object_t *object, dico_t *scene_components,
    window_t *win)
{
    dico_t *cursor = object->components;

    if (cursor == NULL) {
        return;
    }
    do {
        if (my_strstartswith(cursor->key, SET_EVENT) == 1) {
            check_event(cursor->value, object, win, scene_components);
        }
        cursor = cursor->next;
    } while (cursor != object->components);
}

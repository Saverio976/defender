/*
** EPITECH PROJECT, 2022
** bgs lib
** File description:
** start
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my_bgs.h"

void window_set_framerate_limit(window_t *win, unsigned int limit)
{
    sfRenderWindow_setFramerateLimit(win->win, limit);
}

static int init_method(window_t *win, void *(*create)(void), void (*destroy)(void *))
{
    if (create != NULL) {
        win->data = create();
        if (win->data) {
            return 84;
        }
    } else {
        win->data = NULL;
    }
    win->destroy = destroy;
    return (0);
}

window_t *create_window(sfVideoMode mode, const char *title, void *(*create)(void),
    void (*destroy)(void *))
{
    window_t *win = malloc(sizeof(window_t));

    if (win == NULL || title == NULL) {
        return NULL;
    }
    win->win = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    if (win->win == NULL) {
        return NULL;
    }
    win->scenes = list_create();
    if (win->scenes == NULL) {
        return NULL;
    }
    if (init_method(win, create, destroy) == 84) {
        return NULL;
    }
    win->scene_index = 0;
    return win;
}

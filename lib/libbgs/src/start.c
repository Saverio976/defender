/*
** EPITECH PROJECT, 2022
** bgs lib
** File description:
** start
*/

#include <SFML/Graphics.h>
#include "my_bgs.h"

int init_method(window_t *win, void *(*create)(void), void (*destroy)(void *))
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
}

window_t *init(sfVideoMode mode, const char *title, void *(*create)(void),
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
    return win;
}

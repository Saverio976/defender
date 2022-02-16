/*
** EPITECH PROJECT, 2022
** libgs
** File description:
** andle events
*/

#include <SFML/Graphics.h>
#include "my_bgs.h"

int event_handling(sfRenderWindow *win)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(win, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(win);
        }
    }
    return BGS_OK;
}

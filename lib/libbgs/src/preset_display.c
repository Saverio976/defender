/*
** EPITECH PROJECT, 2022
** Defender
** File description:
** preset display
*/

#include "my_bgs.h"

void display_sprite(object_t *object, __attribute__((unused)) void *scene_data,
    __attribute__((unused)) void *win_data, sfRenderWindow *win)
{
    sfRenderWindow_drawSprite(win, object->drawable.sprite, NULL);
}

void display_text(object_t *object, __attribute__((unused)) void *scene_data,
    __attribute__((unused)) void *win_data, sfRenderWindow *win)
{
    sfRenderWindow_drawText(win, object->drawable.text, NULL);
}

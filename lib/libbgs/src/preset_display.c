/*
** EPITECH PROJECT, 2022
** Defender
** File description:
** preset display
*/

#include "my_bgs.h"

void display_sprite(object_t *object,
    __attribute__((unused)) dico_t *scene_compoenents,
    __attribute__((unused)) dico_t *win_components, sfRenderWindow *win)
{
    if (object->type != SPRITE) {
        return;
    }
    sfRenderWindow_drawSprite(win, object->drawable.sprite, NULL);
}

void display_text(object_t *object,
    __attribute__((unused)) dico_t *scene_components,
    __attribute__((unused)) dico_t *win_components, sfRenderWindow *win)
{
    if (object->type != TEXT) {
        return;
    }
    sfRenderWindow_drawText(win, object->drawable.text, NULL);
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** function for button hover
*/

#include "my_bgs.h"
#include "my_bgs_components.h"

void on_hover_menu_but(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt)
{
    if (obj->type == SPRITE) {
        sfSprite_setScale(obj->drawable.sprite, (sfVector2f) {1.02, 1.02});
    }
}

void off_hover_menu_but(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt)
{
    if (obj->type == SPRITE) {
        sfSprite_setScale(obj->drawable.sprite, (sfVector2f) {1.00, 1.00});
    }
}

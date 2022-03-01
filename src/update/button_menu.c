/*
** EPITECH PROJECT, 2022
** defender
** File description:
** function for button hover
*/

#include "my_bgs.h"
#include "my_bgs_components.h"
#include "my_puts.h"

void click_play_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt)
{
    win->scene_index = 1;
}

void click_settings_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt)
{
    win->scene_index = 2;
}

void click_quit_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt)
{
    sfRenderWindow_close(win->win);
}

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

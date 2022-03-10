/*
** EPITECH PROJECT, 2022
** defender
** File description:
** function for button hover
*/

#include "defender_game_data.h"
#include "my_bgs_components.h"

void click_play_button(__attribute((unused)) object_t *obj,
    __attribute((unused)) scene_t *scene, window_t *win,
    __attribute((unused)) set_event_t *evt)
{
    win->scene_index = 1;
}

void click_settings_button(__attribute((unused)) object_t *obj,
    __attribute((unused)) scene_t *scene, window_t *win,
    __attribute((unused)) set_event_t *evt)
{
    win->scene_index = 2;
}

void click_quit_button(__attribute((unused)) object_t *obj,
    __attribute((unused)) scene_t *scene, window_t *win,
    __attribute((unused)) set_event_t *evt)
{
    sfRenderWindow_close(win->win);
}

void on_hover_menu_but(__attribute((unused)) object_t *obj,
    __attribute((unused)) scene_t *scene,
    __attribute((unused)) window_t *win,
    __attribute((unused)) set_event_t *evt)
{
    any_t *size = dico_t_get_any(obj->components, SIZE);
    float scale = 1.02;

    if (size != NULL && size->type == FLOAT) {
        scale = size->value.f + (size->value.f * 0.02);
    }
    if (obj->type == SPRITE) {
        sfSprite_setScale(obj->drawable.sprite, (sfVector2f) {scale, scale});
    }
}

void off_hover_menu_but(object_t *obj,
    __attribute((unused)) scene_t *scene,
    __attribute((unused)) window_t *win,
    __attribute((unused)) set_event_t *evt)
{
    any_t *size = dico_t_get_any(obj->components, SIZE);
    float scale = 1.00;

    if (size != NULL && size->type == FLOAT) {
        scale = size->value.f;
    }
    if (obj->type == SPRITE) {
        sfSprite_setScale(obj->drawable.sprite, (sfVector2f) {scale, scale});
    }
}

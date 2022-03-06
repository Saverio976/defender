/*
** EPITECH PROJECT, 2022
** defender
** File description:
** button resume
*/

#include "defender_game_data.h"

void click_resume_button(__attribute__((unused)) object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    click_pause_button(obj, scene, win, evt);
}

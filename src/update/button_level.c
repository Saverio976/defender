/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update button level
*/

#include "defender.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "my_puts.h"

void click_level_button(object_t *obj,
    __attribute((unused)) scene_t *scene, window_t *win,
    set_event_t *evt)
{
    launch_game(obj, scene, win, evt);
}

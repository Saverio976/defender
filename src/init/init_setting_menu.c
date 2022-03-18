/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init setting menu
*/

#include "defender.h"

int init_setting_menu(window_t *win)
{
    scene_t *scene = create_scene(win, sfBlack);

    return create_button(scene, SETTING_MENU);
}

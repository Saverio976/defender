/*
** EPITECH PROJECT, 2021
** defender
** File description:
** project header
*/

#ifndef defender_H_
    #define defender_H_

    #include "my_bgs.h"

    #define RET_OK 0
    #define RET_INVALID_INPUT 1
    #define RET_ERR_MALLOC 2

static const char MAIN_MENU[] = "./assets/data/game/menu/main.json";

window_t *init_defender(int ac, char **av);
int init_menu(window_t *win);

#endif

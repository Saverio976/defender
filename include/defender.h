/*
** EPITECH PROJECT, 2021
** defender
** File description:
** project header
*/

#ifndef defender_H_
    #define defender_H_

    #define RET_OK 0
    #define RET_INVALID_INPUT 1
    #define RET_ERR_MALLOC 2

static const char MAIN_MENU[] = "./assets/data/game/menu/main.json";

int init_defender(int ac, char **av);

#endif

/*
** EPITECH PROJECT, 2021
** defender
** File description:
** the main entry point for the project
*/

#include "defender.h"

int main(int ac, char **av)
{
    window_t *win = init_defender(ac, av);

    if (win == NULL) {
        return (84);
    }
    loop(win);
    remove_window(win);
    return 0;
}

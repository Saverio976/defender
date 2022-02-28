/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init defender
** defender
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "defender.h"
#include "my_bgs.h"
#include "my_json.h"

window_t *init_defender(int ac, char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    char const title[] = "DEFENDER";
    sfUint32 style = sfClose | sfResize;
    window_t *win = create_window(mode, title, style);

    if (win == NULL || init_menu(win) != RET_OK) {
        return NULL;
    }
    return win;
}

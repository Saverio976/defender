/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init defender
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "defender_game_data.h"
#include "defender.h"
#include "my_bgs.h"
#include "my_json.h"

window_t *init_defender(__attribute__((unused)) int ac,
        __attribute__((unused)) char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    char const title[] = "DEFENDER";
    sfUint32 style = sfClose | sfResize;
    window_t *win = create_window(mode, title, style);

    if (win == NULL || init_main_menu(win) != RET_OK ||
        init_level_menu(win) != RET_OK || init_game_data(win) != RET_OK) {
        return NULL;
    }
    return win;
}

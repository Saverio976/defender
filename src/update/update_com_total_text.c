/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update com display
*/

#include <stdlib.h>
#include "defender_game_data.h"
#include "my_conversions.h"
#include "my_bgs.h"
#include "my_dico.h"
#include "my_strings.h"

void update_com_total_text(object_t *obj,
        __attribute__((unused)) scene_t *scene, window_t *win,
        float dtime)
{
    static float time_update = 0;
    char *tmp = NULL;
    char buff[255] = {"com: "};
    game_data_t *game = NULL;

    game = dico_t_get_value(win->components, GAME_DATA);
    if (game == NULL) {
        return;
    }
    time_update += dtime;
    if (time_update > 0.5) {
        time_update -= 0.5;
        tmp = my_itoa(game->com);
        if (tmp == NULL) {
            return;
        }
        my_strcat(buff, tmp);
        free(tmp);
        sfText_setString(obj->drawable.text, buff);
    }
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** utility function for an ennemy
*/

#include "defender_game_data.h"
#include "list.h"
#include "my_bgs.h"
#include "defender_ennemy.h"
#include "my_dico.h"

void check_ennemy_alive(object_t *obj, float dtime, window_t *win,
        scene_t *scene)
{
    ennemy_t *enn = NULL;
    game_data_t *game = NULL;

    if (obj == NULL || win == NULL || scene == NULL) {
        return;
    }
    enn = dico_t_get_value(obj->components, OBJ_COMP_ENNSTRUCT);
    game = dico_t_get_value(win->components, GAME_DATA);
    if (enn == NULL || game == NULL) {
        return;
    }
    enn->time_last += dtime;
    enn->time_last_update += dtime;
    if (enn->life <= 0) {
        obj->is_visible = false;
        game->com += enn->com;
        game->xp += enn->xp;
    }
}

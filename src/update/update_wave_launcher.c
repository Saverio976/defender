/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update wave to launch ennemy
*/

#include <stddef.h>
#include "my_bgs.h"
#include "defender.h"
#include "defender_ennemy.h"

void update_wave_launcher(object_t *obj, scene_t *scene, window_t *win,
        float dtime)
{
    static float time = 0.0;
    list_ptr_t *list_enemy = NULL;
    ennemy_load_t *enn = NULL;

    time += dtime;
    if (scene == NULL || obj == NULL) {
        return;
    }
    list_enemy = dico_t_get_value(obj->components, OBJ_COMP_MANAGEWAVE);
    if (list_enemy == NULL) {
        return;
    }
    enn = list_enemy->start->var;
    if (enn != NULL && time > enn->time) {
        time = 0;
        create_ennemy(scene, enn->ennemy_file, enn->spawn);
        rm_fst_elem(list_enemy);
    }
}

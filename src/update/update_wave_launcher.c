/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update wave to launch ennemy
*/

#include <stdlib.h>
#include "list.h"
#include "my_bgs.h"
#include "defender.h"
#include "defender_ennemy.h"

static void free_ennemy_load(load_t *enn, list_ptr_t *list_enemy)
{
    free(enn->ennemy_file);
    free(enn);
    rm_fst_elem(list_enemy);
}

void update_wave_launcher(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win, float dtime)
{
    static float time = 0.0;
    list_ptr_t *list_enemy = NULL;
    load_t *enn = NULL;

    if (scene == NULL || obj == NULL || scene->pause == true) {
        return;
    }
    list_enemy = dico_t_get_value(obj->components, OBJ_COMP_MANAGEWAVE);
    if (list_enemy == NULL || list_enemy->len <= 0) {
        return;
    }
    if (list_enemy->start != NULL) {
        enn = list_enemy->start->var;
    }
    time += dtime;
    if (list_enemy->start != NULL && time > enn->time) {
        time -= enn->time;
        create_ennemy(scene, enn->ennemy_file, enn->spawn);
        free_ennemy_load(enn, list_enemy);
    }
}

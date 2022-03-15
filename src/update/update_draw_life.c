/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update the life printer of nico
*/

#include <stdlib.h>
#include <sys/cdefs.h>
#include "defender.h"
#include "my_bgs.h"
#include "my_conversions.h"
#include "my_dico.h"
#include "my_json.h"
#include "my_strings.h"

void update_draw_life(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win,
        __attribute__((unused)) float dtime)
{
    level_data_t *lvl = NULL;
    char *value = NULL;
    char to_print[50] = "Nico Life : ";

    lvl = dico_t_get_value(scene->components, "LEVEL DATA");
    if (lvl == NULL) {
        return;
    }
    value = my_itoa(lvl->tower_nico_life);
    if (value == NULL) {
        value = my_strdup("error!");
    }
    my_strcat(to_print, value);
    sfText_setString(obj->drawable.text, to_print);
    free(value);
    if (lvl->tower_nico_life <= 0) {
        win->scene_index = 1;
    }
}

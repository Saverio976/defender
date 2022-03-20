/*
** EPITECH PROJECT, 2022
** defender
** File description:
** spawn a damage information
*/

#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "my_conversions.h"
#include "my_strings.h"
#include "my_bgs.h"

static void update_damage_text(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win,
        float dtime)
{
    static float time_free = 0;

    time_free += dtime;
    if (time_free > 2) {
        list_add_to_start(scene->to_remove, obj);
        time_free -= 2;
    } else {
        sfText_setFillColor(obj->drawable.text, sfColor_fromRGBA(190, 43,
                    53, 180));
        sfText_setCharacterSize(obj->drawable.text, 23);
        obj->bigdata.text_bigdata.pos.y -= 0.5;
    }
}

void create_damage_enn_info(scene_t *scene, sfVector2f pos, int nb_dmg)
{
    object_t *object = NULL;
    char buff[256] = {"+"};
    char *tmp = NULL;

    tmp = my_itoa(nb_dmg);
    if (tmp == NULL) {
        return;
    }
    my_strcat(buff, tmp);
    free(tmp);
    object = create_object(update_damage_text, NULL, scene);
    if (object == NULL) {
        return;
    }
    object_set_text(object, "./assets/font/menlo.ttf", buff, pos);
    list_add_to_end(scene->displayables, object);
    list_add_to_end(scene->updates, object);
}

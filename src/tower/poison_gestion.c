/*
** EPITECH PROJECT, 2022
** defender
** File description:
** poison gestion
*/

#include <stdlib.h>
#include "defender_game_data.h"

void update_poison(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, float time)
{
    poison_t *poison = dico_t_get_value(obj->components, "data");
    list_ptr_t *list = NULL;

    if (poison == NULL || scene->pause == true) {
        return;
    }
    poison->timer -= time;
    if (poison->timer < 0) {
        list = dico_t_get_value(scene->components, POISON_LIST);
        if (list != NULL) {
            check_list(list, poison);
        }
        list_add_to_end(scene->to_remove, obj);
    }
}

void add_to_poison_list(scene_t *scene, object_t *obj)
{
    list_ptr_t *list = dico_t_get_value(scene->components, POISON_LIST);
    poison_t *poison = dico_t_get_value(obj->components, "data");

    if (poison == NULL) {
        return;
    }
    if (list == NULL) {
        list = list_create();
        if (list == NULL) {
            return;
        }
        scene->components = dico_t_add_data(scene->components, POISON_LIST,
            list, free_list_void);
    }
    list_add_to_end(list, poison);
}

void display_poison(object_t *obj, __attribute__((unused)) dico_t
    *scene_comp, __attribute__((unused)) dico_t *win_com, sfRenderWindow *win)
{
    poison_t *poison = dico_t_get_value(obj->components, "data");

    if (poison != NULL) {
        sfRenderWindow_drawCircleShape(win, poison->scope, NULL);
    }
    sfRenderWindow_drawSprite(win, obj->drawable.sprite, NULL);
}

void destroy_poison_data(void *data)
{
    poison_t *poison = data;

    if (data == NULL) {
        return;
    } else if (poison->scope != NULL) {
        sfCircleShape_destroy(poison->scope);
    }
    free(poison);
}

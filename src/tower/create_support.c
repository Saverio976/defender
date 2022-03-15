/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create support
*/

#include "defender_game_data.h"

static object_t *support_set_event(scene_t *scene, object_t *obj)
{
    if (event_add_node(create_event(display_scope, true, obj, NULL),
        (node_params_t) {sfMouseLeft, sfKeyA, MOUSE}) != RET_OK ||
        event_add_node(create_event(hide_scope, false, obj, NULL),
        (node_params_t) {sfMouseLeft, sfKeyA, MOUSE}) != RET_OK) {
        return NULL;
    }
    list_add_to_i(scene->displayables, obj,
        (int) dico_t_get_value(scene->components, ENNEMY_ID));
    list_add_to_end(scene->updates, obj);
    return obj;
}

object_t *place_support(any_t *size, scene_t *scene, sfVector2f pos)
{
    int path_id = -1;
    object_t *obj = NULL;

    if (size == NULL || size->type != INT) {
        return NULL;
    }
    for (int i = 0; i < 3; i++) {
        if (SIZE_ARR[i] == size->value.i) {
            path_id = i;
        }
    }
    obj = create_object(NULL, NULL, scene);
    if (path_id < 0 || obj == NULL || object_set_sprite(obj,
        SUPPORT_PATH[path_id], (sfIntRect) {-1, -1, -1, -1}, pos) != RET_OK) {
        return NULL;
    }
    return support_set_event(scene, obj);
}

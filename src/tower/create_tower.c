/*
** EPITECH PROJECT, 2022
** defender
** File description:
** place tower
*/

#include <stdlib.h>
#include "defender_game_data.h"

static void destroy_tower_data(void *data)
{
    tower_data_t *tower_data = data;

    if (tower_data != NULL && tower_data->scope != NULL) {
        free_list(tower_data->scope);
        free(tower_data);
    } else if (tower_data != NULL) {
        free(tower_data);
    }
}

static object_t *set_data(object_t *object, dico_t *tower)
{
    any_t *cadence = dico_t_get_any(tower, "cadence");
    any_t *fly = dico_t_get_any(tower, "fly");
    any_t *damage = dico_t_get_any(tower, "damage");
    tower_data_t *tower_data = malloc(sizeof(tower_data_t));

    if (tower_data == NULL || cadence == NULL || fly == NULL ||
        damage == NULL) {
        return NULL;
    }
    tower_data->cadence = cadence->value.f;
    tower_data->damage = damage->value.i;
    tower_data->fly = (fly->value.i == 1) ? true : false;
    tower_data->scope = NULL;
    tower_data->dtime = 0;
    object->components = dico_t_add_data(object->components, TOWER_DATA,
        tower_data, destroy_tower_data);
    if (object->components == NULL) {
        return NULL;
    }
    return object;
}

static object_t *set_tower(dico_t *tower, scene_t *scene, sfVector2f pos,
    int *rect)
{
    object_t *obj = NULL;
    any_t *path = NULL;

    if (tower == NULL || scene == NULL || rect == NULL) {
        return NULL;
    }
    path = dico_t_get_any(tower, "path");
    obj = create_object(&update_tower, NULL, scene);
    if (path == NULL || obj == NULL ||
        object_set_sprite(obj, path->value.str, (sfIntRect) {rect[0], rect[1],
        rect[2], rect[3]}, pos) != RET_OK) {
        return NULL;
    }
    list_add_to_i(scene->displayables, obj, (int)
        dico_t_get_value(scene->components, ENNEMY_ID));
    list_add_to_end(scene->updates, obj);
    free(rect);
    return set_data(obj, tower);
}

int create_tower(scene_t *scene, dico_t *tower_dico, sfVector2f pos)
{
    object_t *tower = NULL;
    object_t *support = NULL;
    dico_t *components[2] = {NULL, NULL};

    if (scene == NULL || tower_dico == NULL) {
        return RET_ERR_MALLOC;
    }
    tower = set_tower(tower_dico, scene, pos, get_any_int_array(
        dico_t_get_any(tower_dico, "rect")));
    support = place_support(dico_t_get_any(tower_dico, "size"), scene, pos);
    if (tower == NULL || support == NULL) {
        return RET_ERR_MALLOC;
    }
    components[0] = tower->components;
    components[1] = support->components;
    if (set_scope(tower_dico, components, support, scene) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

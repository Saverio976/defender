/*
** EPITECH PROJECT, 2022
** defender
** File description:
** place tower
*/

#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <stdlib.h>
#include "list.h"
#include "my_strings.h"
#include "defender_game_data.h"
#include "my_bgs.h"
#include "my_dico.h"
#include "my_json.h"

void free_list_void(void *data);

static void destroy_tower_data(void *data)
{
    tower_data_t *tower_data = data;

    if (data == NULL) {
        return;
    }
    if (tower_data->scope != NULL) {
        sfCircleShape_destroy(tower_data->scope);
    }
    if (tower_data->sprite_bullet != NULL) {
        free(tower_data->sprite_bullet);
    }
    free(tower_data);
}

static tower_data_t *set_data(object_t *object, dico_t *tower)
{
    any_t *cadence = dico_t_get_any(tower, "cadence");
    any_t *fly = dico_t_get_any(tower, "fly");
    any_t *damage = dico_t_get_any(tower, "damage");
    any_t *scope = dico_t_get_any(tower, "scope");
    tower_data_t *tower_data = malloc(sizeof(tower_data_t));

    if (tower_data == NULL || cadence == NULL || fly == NULL ||
        damage == NULL || scope == NULL) {
        return NULL;
    }
    tower_data->cadence = cadence->value.f;
    tower_data->damage = damage->value.i;
    tower_data->fly = (fly->value.i == 1) ? true : false;
    tower_data->scope = NULL;
    tower_data->dtime = 0;
    tower_data->scope_rad = scope->value.i * 40;
    object->components = dico_t_add_data(object->components, TOWER_DATA,
        tower_data, destroy_tower_data);
    return (object->components == NULL) ? NULL : tower_data;
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
    list_add_to_i(scene->displayables, obj,
        (int) dico_t_get_value(scene->components, ENNEMY_ID));
    list_add_to_end(scene->updates, obj);
    free(rect);
    obj = fill_data_bullet(obj, tower, set_data(obj, tower));
    return obj;
}

void add_to_support_list(scene_t *scene, object_t *support)
{
    list_ptr_t *list = dico_t_get_value(scene->components, TOWER_LIST);

    if (list == NULL) {
        list = list_create();
        if (list == NULL) {
            return;
        }
        scene->components = dico_t_add_data(scene->components, TOWER_LIST,
            list, free_list_void);
        if (scene->components == NULL) {
            return;
        }
    }
    list_add_to_end(list, support);
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
    add_to_support_list(scene, support);
    if (tower == NULL || support == NULL) {
        return RET_ERR_MALLOC;
    }
    components[0] = tower->components;
    components[1] = support->components;
    if (set_scope(components, support) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

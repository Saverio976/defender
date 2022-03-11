/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create ennemy form a json
*/

#include <SFML/Graphics/Color.h>
#include <stdlib.h>
#include "list.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "my_dico.h"
#include "my_json.h"
#include "my_strings.h"
#include "defender.h"
#include "defender_ennemy.h"
#include "defender_game_data.h"

void free_list_void(void *data);

static sfVector2f get_pos_map_ennemy(scene_t *scene, int nb_spawn)
{
    char **map = NULL;
    int nb_start = 0;
    int is_found = 0;
    sfVector2i pos = {0, 0};
    int padding = MAP_SIZE_SQUARE_X;

    map = dico_t_get_value(scene->components, SCENE_COMP_MAP);
    if (map == NULL) {
        return ((sfVector2f) {0, 0});
    }
    for (pos.y = 0; is_found == 0 && map[pos.y] != NULL; pos.y++) {
        for (pos.x = 0; is_found == 0 && map[pos.y][pos.x] != '\0'; pos.x++) {
            nb_start += (map[pos.y][pos.x] == MAP_SPAWN_CHAR) ? 1 : 0;
            is_found = (nb_start == nb_spawn + 1) ? 1 : 0;
        }
    }
    if (is_found == 0) {
        return ((sfVector2f) {0, 0});
    }
    return ((sfVector2f) {--pos.x * padding, --pos.y * padding});
}

static int fill_vector2i(any_t *json, sfIntRect *rect)
{
    any_t *any = NULL;

    any = get_from_any(json, "da", "int_rect", 0);
    if (any == NULL) {
        return (RET_OK);
    }
    if (get_from_any(json, "da", "int_rect", 1) == NULL ||
            get_from_any(json, "da", "int_rect", 2) == NULL ||
            get_from_any(json, "da", "int_rect", 3) == NULL) {
        return (RET_INVALID_INPUT);
    }
    rect->left = any->value.i;
    any = get_from_any(json, "da", "int_rect", 1);
    rect->top = any->value.i;
    any = get_from_any(json, "da", "int_rect", 2);
    rect->width = any->value.i;
    any = get_from_any(json, "da", "int_rect", 3);
    rect->height = any->value.i;
    return (RET_OK);
}

static int set_obj_ennemy(scene_t *scene, object_t *obj, any_t *json,
        int nb_spawn)
{
    any_t *any = NULL;
    sfIntRect rect = {-1, -1, -1, -1};
    int ret_code = 0;
    sfVector2f pos = {0};

    any = get_from_any(json, "d", "path");
    if (any == NULL || any->type != STR) {
        return (RET_INVALID_INPUT);
    }
    ret_code = fill_vector2i(json, &rect);
    if (ret_code != RET_OK) {
        return (ret_code);
    }
    pos = get_pos_map_ennemy(scene, nb_spawn);
    ret_code = object_set_sprite(obj, any->value.str, rect, pos);
    list_add_to_i(scene->displayables, obj,
        (int) dico_t_get_value(scene->components, ENNEMY_ID));
    list_add_to_end(scene->updates, obj);
    return (ret_code);
}

void add_obj_to_scene_list(scene_t *scene, object_t *obj)
{
    list_ptr_t *list = NULL;

    if (scene == NULL || obj == NULL) {
        return;
    }
    list = dico_t_get_value(scene->components, LIST_ENNEMY);
    if (list == NULL) {
        list = list_create();
        scene_add_components(scene, list, LIST_ENNEMY, free_list_void);
    }
    list_add_to_end(list, obj);
}

int create_ennemy(scene_t *scene, char const *path_json, int nb_spawn)
{
    any_t *json = NULL;
    object_t *obj = NULL;

    if (path_json == NULL || scene == NULL) {
        return (RET_INVALID_INPUT);
    }
    json = parse_json_file(path_json);
    if (json == NULL) {
        return (RET_INVALID_INPUT);
    }
    obj = create_object(update_ennemy, NULL, scene);
    if (obj == NULL) {
        return (RET_ERR_MALLOC);
    }
    set_obj_ennemy(scene, obj, json, nb_spawn);
    object_add_components(obj, init_ennemy(json), OBJ_COMP_ENNSTRUCT, free);
    destroy_any(json);
    add_obj_to_scene_list(scene, obj);
    return (RET_OK);
}

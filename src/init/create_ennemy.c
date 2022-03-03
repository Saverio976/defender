/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create ennemy form a json
*/

#include "my_bgs.h"
#include "my_json.h"
#include "my_strings.h"
#include "defender.h"
#include "defender_ennemy.h"

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

static int set_obj_ennemy(object_t *obj, any_t *json, sfVector2f pos)
{
    any_t *any = NULL;
    char *path_sprite = NULL;
    sfIntRect rect = {-1, -1, -1, -1};
    int ret_code = 0;

    any = get_from_any(json, "d", "path");
    if (any == NULL || any->type != STR) {
        return (RET_INVALID_INPUT);
    }
    path_sprite = my_strdup(any->value.str);
    ret_code = fill_vector2i(json, &rect);
    if (ret_code != RET_OK) {
        return (ret_code);
    }
    ret_code = object_set_sprite(obj, path_sprite, rect, pos);
    return (ret_code);
}

int create_ennemy(scene_t *scene, char const *path_json, sfVector2f pos)
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
    set_obj_ennemy(obj, json, pos);
    destroy_any(json);
    return (RET_OK);
}

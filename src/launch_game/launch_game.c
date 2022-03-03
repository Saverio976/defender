/*
** EPITECH PROJECT, 2022
** defender
** File description:
** launch game
*/

#include <stdlib.h>
#include "my_puts.h"
#include "my_conversions.h"
#include "my_strings.h"
#include "my_json.h"
#include "defender.h"

static int create_game_from_level_data(any_t *level_data, object_t *obj,
    scene_t *scene, window_t *win)
{
    any_t *path = dico_t_get_any(level_data->value.dict, "map path");

    if (path == NULL) {
        return RET_INVALID_INPUT;
    }
    create_map(scene, path->value.str, dico_t_get_any(level_data->value.dict,
        "squares path"));
    return RET_OK;
}

int launch_game(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, set_event_t *evt)
{
    any_t *level_data = NULL;
    scene_t *new_scene = create_scene(win, sfBlack);
    char *level_path = NULL;

    if (obj == NULL || scene == NULL || win == NULL || evt == NULL ||
        new_scene == NULL) {
        return RET_INVALID_INPUT;
    }
    level_path = dico_t_get_value(obj->components, "level path");
    if (level_path == NULL) {
        return RET_ERR_MALLOC;
    }
    level_data = parse_json_file(level_path);
    if (level_data == NULL ||
        create_game_from_level_data(level_data, obj, new_scene, win)
        != RET_OK) {
        return RET_ERR_MALLOC;
    }
    printf("win scene len: %d\n", win->scenes->len);
    win->scene_index = 2;
    return RET_OK;
}

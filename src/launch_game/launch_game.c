/*
** EPITECH PROJECT, 2022
** defender
** File description:
** launch game
*/

#include <stdlib.h>
#include "my_puts.h"
#include "my_conversions.h"
#include "my_wordarray.h"
#include "my_strings.h"
#include "my_json.h"
#include "defender.h"

void update_wave_launcher(object_t *object, scene_t *scene, window_t *win,
    float time)
{
    list_ptr_t *load_list = dico_t_get_any(object->components, "load list");
    list_t *elem = NULL;
    load_t *load = NULL;

    if (load_list == NULL) {
        return;
    }
    elem = load_list->start;
    for (int i = 0; i < load_list->len; i++, elem = elem->next) {
        load = ((load_t *) elem->var);
        //printf("file: %s; time: %f; spawn: %d\n", load->ennemy_file, load->time, load->spawn);
    }
}

static int create_game_from_level_data(dico_t *level_data, object_t *obj,
    scene_t *scene, window_t *win)
{
    any_t *map_path = dico_t_get_any(level_data, "map path");
    object_t *wave_launcher = create_object(update_wave_launcher, NULL, scene);
    list_ptr_t *load_list = create_load_list(dico_t_get_any(level_data, "wave"),
        dico_t_get_any(level_data, "ennemy file"));

    if (map_path == NULL || wave_launcher == NULL ||
        list_add_to_end(scene->updates, wave_launcher) == NULL ||
        load_list == NULL) {
        return RET_INVALID_INPUT;
    }
    object_set_custom(wave_launcher);
    wave_launcher->components = dico_t_add_data(wave_launcher->components,
        "load list", load_list, destroy_load_list);
    if (wave_launcher == NULL || create_map(scene, map_path->value.str,
        dico_t_get_any(level_data, "squares path")) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    printf("%p %s\n", wave_launcher->components, ((load_t *) ((list_ptr_t *) wave_launcher->components->value)->start->var)->ennemy_file);
    destroy_any(level_data);
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
        create_game_from_level_data(level_data->value.dict, obj, new_scene, win)
        != RET_OK) {
        return RET_ERR_MALLOC;
    }
    win->scene_index = 2;
    return RET_OK;
}

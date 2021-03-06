/*
** EPITECH PROJECT, 2022
** defender
** File description:
** launch game
*/

#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "defender.h"
#include "my_bgs.h"
#include "my_puts.h"
#include "my_conversions.h"
#include "defender_game_data.h"
#include "defender_ennemy.h"
#include "my_wordarray.h"
#include "my_strings.h"

int init_click_checker(scene_t *scene, window_t *win)
{
    object_t *obj = create_object(NULL, NULL, scene);
    set_event_t *evt = NULL;
    node_params_t node = {sfMouseLeft, sfKeyA, MOUSE};

    if (obj == NULL) {
        return RET_ERR_MALLOC;
    }
    object_set_custom(obj);
    evt = create_event(check_open_elem, false, obj, NULL);
    if (event_add_node(evt, node) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    scene->components = dico_t_add_data(scene->components, "window", win, NULL);
    return (scene->components != NULL) ? RET_OK : RET_ERR_MALLOC;
}

static int create_level_data_scene(scene_t *scene, dico_t *lvl_data_json,
    window_t *win, any_t *com)
{
    level_data_t *lvl = NULL;
    any_t *any = NULL;
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);

    lvl = malloc(sizeof(level_data_t));
    if (lvl == NULL || game_data == NULL || com == NULL) {
        return (RET_ERR_MALLOC);
    }
    game_data->com = com->value.i;
    any = dico_t_get_value(lvl_data_json, "tower nico life");
    if (any == NULL || any->type != INT) {
        return (RET_ERR_MALLOC);
    }
    lvl->tower_nico_life = any->value.i;
    scene_add_components(scene, lvl, "LEVEL DATA", free);
    return (create_texts(scene));
}

static int create_game(dico_t *level_data, __attribute__((unused))
    object_t *obj, scene_t *scene, __attribute__((unused)) window_t *win)
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
        dico_t_get_any(level_data, "squares path")) != RET_OK ||
        init_side_menu(win, scene) != RET_OK || set_aud(scene, win) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return create_level_data_scene(scene, level_data, win,
        dico_t_get_any(level_data, "com"));
}

int launch_game(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, set_event_t *evt)
{
    any_t *level_data = NULL;
    scene_t *new_scene = create_scene(win, sfBlack);
    char *level_path = NULL;
    any_t *tower = parse_json_file("./assets/data/game/tower/standart.json");

    if (obj == NULL || scene == NULL || win == NULL || evt == NULL ||
        new_scene == NULL || tower == NULL ||
        init_click_checker(new_scene, win) != RET_OK) {
        return RET_INVALID_INPUT;
    }
    level_path = dico_t_get_value(obj->components, "level path");
    level_data = parse_json_file(level_path);
    if (level_data == NULL || create_game(level_data->value.dict, obj,
        new_scene, win) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    destroy_any(level_data);
    win->scene_index = win->scenes->len - 1;
    destroy_any(tower);
    return RET_OK;
}

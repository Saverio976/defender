/*
** EPITECH PROJECT, 2022
** defender
** File description:
** launch game
*/

#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "list.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "my_dico.h"
#include "my_puts.h"
#include "my_conversions.h"
#include "defender_game_data.h"
#include "defender_ennemy.h"
#include "my_wordarray.h"
#include "my_strings.h"
#include "my_json.h"
#include "defender.h"

static int create_level_data_scene(scene_t *scene, dico_t *lvl_data_json)
{
    level_data_t *lvl = NULL;
    any_t *any = NULL;
    object_t *obj_draw_life = NULL;

    lvl = malloc(sizeof(level_data_t));
    if (lvl == NULL) {
        return (RET_ERR_MALLOC);
    }
    any = dico_t_get_value(lvl_data_json, "tower nico life");
    if (any == NULL || any->type != INT) {
        return (RET_ERR_MALLOC);
    }
    lvl->tower_nico_life = any->value.i;
    scene_add_components(scene, lvl, "LEVEL DATA", free);
    obj_draw_life = create_object(update_draw_life, NULL, scene);
    object_set_text(obj_draw_life, "assets/font/menlo.ttf", "life",
            (sfVector2f) {1500, 10});
    list_add_to_end(scene->updates, obj_draw_life);
    list_add_to_end(scene->displayables, obj_draw_life);
    return (RET_OK);
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
        init_side_menu(win, scene) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    create_level_data_scene(scene, level_data);
    return RET_OK;
}

int launch_game(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, set_event_t *evt)
{
    any_t *level_data = NULL;
    scene_t *new_scene = create_scene(win, sfBlack);
    char *level_path = NULL;
    any_t *tower = parse_json_file("./assets/data/game/tower/standart.json");

    if (obj == NULL || scene == NULL || win == NULL || evt == NULL ||
        new_scene == NULL || tower == NULL) {
        return RET_INVALID_INPUT;
    }
    level_path = dico_t_get_value(obj->components, "level path");
    level_data = parse_json_file(level_path);
    if (level_data == NULL || create_game(level_data->value.dict, obj,
        new_scene, win) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    destroy_any(level_data);
    win->scene_index = 2;
    destroy_any(tower);
    return RET_OK;
}

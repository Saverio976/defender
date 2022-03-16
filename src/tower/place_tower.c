/*
** EPITECH PROJECT, 2022
** defender
** File description:
** place tower
*/

#include "my_puts.h"
#include "defender_game_data.h"
#include "defender_ennemy.h"

bool check_pos(int i, int pos_x, char **map, int size)
{
    for (int x = pos_x; x < pos_x + (size * 40); x += 40) {
        if (map[i / 40][x / 40] != '.') {
            return false;
        }
    }
    return true;
}

bool check_place(int size, scene_t *scene, object_t *suppport)
{
    char **map = dico_t_get_value(scene->components, SCENE_COMP_MAP);
    sfVector2i pos;

    if (map == NULL) {
        return false;
    }
    pos.x = ((int) suppport->bigdata.sprite_bigdata.pos.x) - ((int) size / 2);
    pos.y = ((int) suppport->bigdata.sprite_bigdata.pos.y) - ((int) size / 2);
    for (int i = pos.y; i < pos.y + (size * 40); i += 40) {
        if (check_pos(i, pos.x, map, size) == false) {
            return false;
        }
    }
    for (int i = pos.y; i < pos.y + (size * 40); i += 40) {
        for (int x = pos.x; x < pos.x + (size * 40); x += 40) {
            map[i / 40][x / 40] = 'T';
        }
    }
    return true;
}

void place_tower(object_t *obj, scene_t *scene, window_t *win, set_event_t *evt)
{
    int size = (int) dico_t_get_value(obj->components, "tower size");
    object_t *drag_tower = dico_t_get_value(obj->components, "drag tower");
    char *tower_path = dico_t_get_value(obj->components, "tower path");
    any_t *tower = NULL;

    if (tower_path == NULL || drag_tower == NULL) {
        return;
    }
    tower = parse_json_file(tower_path);
    if (tower == NULL || tower->type != DICT ||
        check_place(size, scene, obj) == false) {
        return;
    }
    create_tower(scene, tower->value.dict, obj->bigdata.sprite_bigdata.pos);
    list_add_to_end(scene->to_remove, obj);
    list_add_to_end(scene->to_remove, drag_tower);
    destroy_any(tower);
}

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

bool check_place(int size, scene_t *scene, object_t *suppport, window_t *win)
{
    char **map = dico_t_get_value(scene->components, SCENE_COMP_MAP);
    sfVector2i pos;
    int px_size = ((int) size / 2) * 40;

    if (map == NULL) {
        return false;
    }
    pos.x = ((int) suppport->bigdata.sprite_bigdata.pos.x) - px_size;
    pos.y = ((int) suppport->bigdata.sprite_bigdata.pos.y) - px_size;
    for (int i = pos.y; i < pos.y + (size * 40); i += 40) {
        if (check_pos(i, pos.x, map, size) == false) {
            return create_txt_place_err(suppport, scene, win);
        }
    }
    for (int i = pos.y; i < pos.y + (size * 40); i += 40) {
        for (int x = pos.x; x < pos.x + (size * 40); x += 40) {
            map[i / 40][x / 40] = 'T';
        }
    }
    return true;
}

bool check_drag_pos(window_t *win, int size)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win->win);
    int px_size = (size / 2) * 40;

    if (pos.x - px_size < 0 || pos.x + px_size > 1839 ||
        pos.y - px_size < 0 || pos.y + px_size > 1079) {
        return false;
    }
    return true;
}

void place_tower(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    int size = (int) dico_t_get_value(obj->components, "tower size");
    object_t *drag_tower = dico_t_get_value(obj->components, "drag tower");
    char *tower_path = dico_t_get_value(obj->components, "tower path");
    any_t *tower = NULL;

    if (tower_path == NULL || drag_tower == NULL ||
        check_drag_pos(win, size) == false) {
        return;
    }
    tower = parse_json_file(tower_path);
    if (tower == NULL) {
        return;
    }
    if (tower->type == DICT && check_place(size, scene, obj, win) == true) {
        create_tower(scene, tower->value.dict, obj->bigdata.sprite_bigdata.pos);
        list_add_to_end(scene->to_remove, obj);
        list_add_to_end(scene->to_remove, drag_tower);
    }
    destroy_any(tower);
}

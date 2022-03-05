/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update ennemy
*/

#include "my_bgs.h"
#include "my_dico.h"
#include "my_wordarray.h"
#include "my_strings.h"
#include "defender_ennemy.h"

static sfVector2f move_ennemy(char **map, sfVector2i pos, ennemy_t *enn)
{
    int len = my_wordarray_len(map);
    sfVector2f new = {pos.x, pos.y};

    if (pos.y + 1 < len && pos.x < my_strlen(map[pos.y + 1]) && pos.y + 1 !=
            enn->last_pos.y && map[pos.y + 1][pos.x] == MAP_ROAD_CHAR) {
        new = (sfVector2f) {pos.y + 1, pos.x};
    }
    if (pos.y - 1 >= 0 && pos.x < my_strlen(map[pos.y - 1]) && pos.y - 1 !=
            enn->last_pos.y && map[pos.y - 1][pos.x] == MAP_ROAD_CHAR) {
        new = (sfVector2f) {pos.y - 1, pos.x};
    }
    if (pos.y < len && pos.x - 1 < my_strlen(map[pos.y]) && pos.x - 1 !=
            enn->last_pos.x && map[pos.y][pos.x - 1] == MAP_ROAD_CHAR) {
        new = (sfVector2f) {pos.y, pos.x - 1};
    }
    if (pos.y < len && pos.x + 1 < my_strlen(map[pos.y]) && pos.x + 1 !=
            enn->last_pos.x && map[pos.y][pos.x + 1] == MAP_ROAD_CHAR) {
        new = (sfVector2f) {pos.y, pos.x + 1};
    }
    return (new);
}

void update_ennemy(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, __attribute__((unused)) float dtime)
{
    char **map = NULL;
    ennemy_t *ennemy_me = NULL;
    sfVector2f pos_f = {0};
    sfVector2i pos_i = {0};

    map = dico_t_get_value(scene->components, SCENE_COMP_MAP);
    if (map == NULL || obj->type != SPRITE) {
        return;
    }
    ennemy_me = dico_t_get_value(obj->components, OBJ_COMP_ENNSTRUCT);
    if (ennemy_me == NULL) {
        return;
    }
    pos_f = obj->bigdata.sprite_bigdata.pos;
    pos_i.x = pos_f.x / MAP_SIZE_SQUARE_X;
    pos_i.y = pos_f.y / MAP_SIZE_SQUARE_Y;
    pos_f = move_ennemy(map, pos_i, ennemy_me);
    obj->bigdata.sprite_bigdata.pos.x = pos_f.x * MAP_SIZE_SQUARE_X;
    obj->bigdata.sprite_bigdata.pos.y = pos_f.y * MAP_SIZE_SQUARE_Y;
}

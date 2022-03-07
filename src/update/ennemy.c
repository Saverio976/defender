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
#include <SFML/System/Vector2.h>

static sfVector2f check_move_y(char **map, sfVector2i pos, ennemy_t *enn,
        int len)
{
    char tab[3] = {MAP_ROAD_CHAR, MAP_NEXT_NICO_CHAR, '\0'};

    if (pos.y + 1 < len && pos.x < my_strlen(map[pos.y + 1]) &&
            pos.y + 1 != enn->last_pos.y &&
            my_strcontainc(tab, map[pos.y + 1][pos.x])) {
        return ((sfVector2f) {pos.x, pos.y + 1});
    }
    if (pos.y - 1 < len && pos.x < my_strlen(map[pos.y - 1]) &&
            pos.y - 1 != enn->last_pos.y &&
            my_strcontainc(tab, map[pos.y - 1][pos.x])) {
        return ((sfVector2f) {pos.x, pos.y - 1});
    }
    return ((sfVector2f) {-1, -1});
}

static sfVector2f check_move_x(char **map, sfVector2i pos, ennemy_t *enn,
        int len)
{
    char tab[3] = {MAP_ROAD_CHAR, MAP_NEXT_NICO_CHAR, '\0'};

    if (pos.y < len && pos.x + 1 < my_strlen(map[pos.y]) &&
            pos.x + 1 != enn->last_pos.x &&
            my_strcontainc(tab, map[pos.y][pos.x + 1])) {
        return ((sfVector2f) {pos.x + 1, pos.y});
    }
    if (pos.y < len && pos.x - 1 < my_strlen(map[pos.y]) &&
            pos.x - 1 != enn->last_pos.x &&
            my_strcontainc(tab, map[pos.y][pos.x - 1])) {
        return ((sfVector2f) {pos.x - 1, pos.y});
    }
    return ((sfVector2f) {-1, -1});
}

static sfVector2f get_right_pos(char **map, sfVector2i pos, ennemy_t *enn)
{
    sfVector2f new = {pos.x, pos.y};
    sfVector2f move = {0};
    int len = 0;

    len = my_wordarray_len(map);
    move = check_move_y(map, pos, enn, len);
    if (move.x != -1 && move.y != -1) {
        return (move);
    }
    move = check_move_x(map, pos, enn, len);
    if (move.x != -1 && move.y != -1) {
        return (move);
    }
    return (new);
}

static void move_ennemy(object_t *obj, ennemy_t *enn, char **map)
{
    sfVector2f pos_f = {0};
    sfVector2i pos_i = {0};

    pos_i.x = ((int) obj->bigdata.sprite_bigdata.pos.x) / MAP_SIZE_SQUARE_X;
    pos_i.y = ((int) obj->bigdata.sprite_bigdata.pos.y) / MAP_SIZE_SQUARE_Y;
    pos_f = get_right_pos(map, pos_i, enn);
    obj->bigdata.sprite_bigdata.pos.x = pos_f.x * MAP_SIZE_SQUARE_X;
    obj->bigdata.sprite_bigdata.pos.y = pos_f.y * MAP_SIZE_SQUARE_Y;
    enn->last_pos.x = pos_i.x;
    enn->last_pos.y = pos_i.y;
}

void update_ennemy(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, float dtime)
{
    char **map = NULL;
    ennemy_t *ennemy_me = NULL;

    map = dico_t_get_value(scene->components, SCENE_COMP_MAP);
    if (map == NULL || obj->type != SPRITE) {
        return;
    }
    ennemy_me = dico_t_get_value(obj->components, OBJ_COMP_ENNSTRUCT);
    if (ennemy_me == NULL) {
        return;
    }
    ennemy_me->time_last += dtime;
    if (obj->is_visible == true && is_obj_touch_nico(obj, map) == 1) {
        update_obj_explosion(obj, dtime);
    } else if (obj->is_visible &&
            ennemy_me->time_last > ennemy_me->load_time) {
        move_ennemy(obj, ennemy_me, map);
        ennemy_me->time_last = 0;
    }
}

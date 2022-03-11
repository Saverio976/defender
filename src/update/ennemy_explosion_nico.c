/*
** EPITECH PROJECT, 2022
** defender
** File description:
** ennemy explose when touch nico
*/

#include <SFML/System/Vector2.h>
#include "my_bgs.h"
#include "my_dico.h"
#include "my_strings.h"
#include "defender_ennemy.h"
#include "my_wordarray.h"

static int check_nico_y(char **map, sfVector2i pos, int len)
{
    if (pos.y + 1 < len && pos.x < my_strlen(map[pos.y + 1]) &&
            map[pos.y + 1][pos.x] == MAP_NICO_CHAR) {
        return (1);
    }
    if (pos.y - 1 < len && pos.x < my_strlen(map[pos.y - 1]) &&
            map[pos.y - 1][pos.x] == MAP_NICO_CHAR) {
        return (1);
    }
    return (0);
}

static int check_nico_x(char **map, sfVector2i pos, int len)
{
    if (pos.y < len && pos.x + 1 < my_strlen(map[pos.y]) &&
            map[pos.y][pos.x + 1] == MAP_NICO_CHAR) {
        return (1);
    }
    if (pos.y < len && pos.x - 1 < my_strlen(map[pos.y]) &&
            map[pos.y][pos.x - 1] == MAP_NICO_CHAR) {
        return (1);
    }
    return (0);
}

int is_obj_touch_nico(object_t *obj, char **map)
{
    sfVector2i pos = {0};
    int len = 0;

    len = my_wordarray_len(map);
    pos.x = ((int) obj->bigdata.sprite_bigdata.pos.x) / MAP_SIZE_SQUARE_X;
    pos.y = ((int) obj->bigdata.sprite_bigdata.pos.y) / MAP_SIZE_SQUARE_Y;
    if (check_nico_y(map, pos, len) == 1 || check_nico_x(map, pos, len) == 1) {
        return (1);
    }
    return (0);
}

void update_obj_explosion(object_t *obj, __attribute__((unused)) float dtime)
{
    ennemy_t *enn = NULL;

    enn = dico_t_get_value(obj->components, OBJ_COMP_ENNSTRUCT);
    if (enn == NULL) {
        return;
    }
    if (enn->time_last > 2.0) {
        obj->is_visible = false;
    }
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** get map from path
*/

#include "defender.h"
#include "my_fs.h"
#include "my_wordarray.h"
#include "my_json.h"
#include "my_strings.h"
#include "my_bgs.h"

static int detect_square_type(char c, scene_t *scene, sfVector2f current_pos,
    dico_t *squares_path)
{
    char type[] = {c, '\0'};
    any_t *square_path = dico_t_get_any(squares_path, type);

    if (square_path == NULL || square_path->type != STR) {
        return RET_INVALID_INPUT;
    }
    return object_set_sprite(create_object(NULL, NULL, scene),
        square_path->value.str, (sfIntRect) {-1, -1, -1, -1}, current_pos);
}

static int create_square_from_map(char **map, scene_t *scene,
    dico_t *squares_path)
{
    int ret = RET_OK;
    sfVector2f current_pos = {30, 30};

    for (int i = 0; map[i] != NULL && ret == RET_OK; i++) {
        for (int x = 0; map[i][x] != '\0' && ret == RET_OK; x++) {
            ret = detect_square_type(map[i][x], scene, current_pos, squares_path);
            current_pos.x += 30;
        }
        current_pos.y += 30;
    }
    return ret;
}

int create_map(scene_t *scene, char const *path, any_t *squares_path)
{
    char **map = NULL;

    if (scene == NULL || path == NULL || squares_path == NULL ||
        squares_path->type != DICT) {
        return RET_INVALID_INPUT;
    }
    map = my_wordarray_from_str(fs_get_content(path), '\n');
    if (map == NULL) {
        return RET_ERR_MALLOC;
    }
    return create_square_from_map(map, scene, squares_path->value.dict);
}

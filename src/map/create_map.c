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
    object_t *square = NULL;

    if (square_path == NULL|| square_path->type != STR) {
        return RET_OK;
    }
    square = create_object(NULL, NULL, scene);
    if (square == NULL ||
        list_add_to_end(scene->displayables, square) == NULL) {
        return RET_ERR_MALLOC;
    }
    return object_set_sprite(square, square_path->value.str,
        (sfIntRect) {-1, -1, -1, -1}, current_pos);
}

static int create_square_from_map(char **map, scene_t *scene,
    dico_t *squares_path)
{
    int ret = RET_OK;
    sfVector2f current_pos = {SQUARE_START_POS, SQUARE_START_POS};

    for (int i = 0; map[i] != NULL && ret == RET_OK; i++) {
        for (int x = 0; map[i][x] != '\0' && ret == RET_OK; x++) {
            ret = detect_square_type(map[i][x], scene, current_pos,
                squares_path);
            current_pos.x += SQUARE_POS_INCREMENTATION;
        }
        current_pos.x = SQUARE_START_POS;
        current_pos.y += SQUARE_POS_INCREMENTATION;
    }
    return ret;
}

int create_map(scene_t *scene, char const *path, any_t *squares_path)
{
    char **map = NULL;
    char *str = NULL;
    int ret = RET_OK;

    if (scene == NULL || path == NULL || squares_path == NULL ||
        squares_path->type != DICT) {
        return RET_INVALID_INPUT;
    }
    str = fs_get_content(path);
    map = my_wordarray_from_str(str, '\n');
    if (map == NULL) {
        return RET_ERR_MALLOC;
    }
    free(str);
    ret = create_square_from_map(map, scene, squares_path->value.dict);
    my_wordarray_free(map);
    return ret;
}

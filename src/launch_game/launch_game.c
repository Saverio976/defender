/*
** EPITECH PROJECT, 2022
** defender
** File description:
** launch game
*/

#include <stdlib.h>
#include "my_conversions.h"
#include "my_strings.h"
#include "my_json.h"
#include "defender.h"

char *cat_path(char *number)
{
    int number_len = my_strlen(number);
    int len = number_len + LEVEL_DATA_lEN + EXTENSION_LEN;
    char *path = malloc(sizeof(char) * len + 1);

    if (path == NULL) {
        return NULL;
    }    
    for (int i = 0; i < len; i++) {
        if (i < LEVEL_DATA_lEN) {
            path[i] = LEVEL_DATA[i];
        } else if (i < LEVEL_DATA_lEN + number_len) {
            path[i] = number[i - LEVEL_DATA_lEN];
        } else {
            path[i] = EXTENSION[i - (LEVEL_DATA_lEN + number_len)];
        }
    }
    return path;
}

any_t *get_level_json(object_t *obj)
{
    any_t *level = NULL;
    char *file = NULL;
    char *number = NULL;

    if (obj == NULL) {
        return NULL;
    }
    level = dico_t_get_any(obj->components, "level");
    if (level == NULL || level->type != INT) {
        return NULL;
    }
    number = my_itoa(level->value.str);
    if (number == NULL) {
        return NULL;
    }
    return parse_json_file(cat_path(number));
}

int launch_game(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt)
{
    any_t *level_data = get_level_json(obj);

    if (obj == NULL || scene == NULL || win == NULL || evt == NULL ||
        level_data == NULL) {
        return RET_INVALID_INPUT;
    }
    create_game_from_level_data(level_data, obj, scene, win);
}

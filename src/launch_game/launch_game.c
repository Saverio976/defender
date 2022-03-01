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

char *cat_path

char *get_file(any_t *any)
{
    char *number = my_itoa(any->value.i);
    int number_len = 0;
    char *path = NULL;
    int len = 0;

    if (number == NULL) {
        return NULL;
    }
    number_len = my_strlen(number);
    len = number_len + LEVEL_DATA_lEN + EXTENSION_LEN + 1;
    path = malloc(sizeof(char) * len);
    if (path == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        if (i < LEVEL_DATA_lEN) {
            path[i] = LEVEL_DATA[i];
        } else {
            path[i] = (i < LEVEL_DATA_lEN + number_len) ? number_len[i - LEVEL_DATA_lEN] : ;
        }
    }
}

any_t *get_level_json(object_t *obj)
{
    any_t *level = NULL;
    char *file = NULL;

    if (obj == NULL) {
        return NULL;
    }
    level = dico_t_get_any(obj->components, "level");
    if (level == NULL || level->type != INT) {
        return NULL;
    }
    file = get_file(level);
    if (file == NULL) {
        return NULL;
    }
}

int launch_game(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt)
{
    any_t *any = get_level_json(obj);

    if (obj == NULL || dico == NULL || win == NULL || evt == NULL) {
        return RET_INVALID_INPUT;
    }
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init game data
*/

#include <stdlib.h>
#include "my_strings.h"
#include "defender_game_data.h"
#include "defender.h"

static void destroy_game_data(void *data)
{
    game_data_t *game_data = data;

    if (game_data == NULL) {
        return;
    }
    dico_t_destroy(game_data->skill_three);
    free(game_data->font);
    free(game_data);
}

static void *cpy_value(any_t *dico)
{
    dico_t *cpy = NULL;
    dico_t *elem = NULL;

    if (dico == NULL || dico->type != DICT) {
        return NULL;
    }
    elem = dico->value.dict;
    do {
        cpy = dico_t_add_data(cpy, elem->key, any_dup(elem->value),
            destroy_any);
        if (cpy == NULL) {
            return NULL;
        }
        elem = elem->next;
    } while (elem != dico->value.dict);
    return cpy;
}

static int copy_skill_three(any_t *skill_three, game_data_t *game_data)
{
    dico_t *elem = NULL;

    if (skill_three == NULL) {
        return RET_INVALID_INPUT;
    }
    elem = skill_three->value.dict;
    do {
        game_data->skill_three = dico_t_add_data(game_data->skill_three,
            elem->key, cpy_value(elem->value), dico_t_destroy_void);
        if (game_data->skill_three == NULL) {
            return RET_INVALID_INPUT;
        }
        elem = elem->next;
    } while (elem != skill_three->value.dict);
    return RET_OK;
}

static int fill_game_data(game_data_t *game_data, dico_t *game_data_file)
{
    any_t *elem = dico_t_get_any(game_data_file, "com");

    game_data->skill_three = NULL;
    if (elem == NULL || elem->type != INT) {
        return RET_INVALID_INPUT;
    }
    game_data->com = elem->value.i;
    elem = dico_t_get_any(game_data_file, "xp");
    if (elem == NULL || elem->type != INT) {
        return RET_INVALID_INPUT;
    }
    game_data->xp = elem->value.i;
    elem = dico_t_get_any(game_data_file, "level progression");
    if (elem == NULL || elem->type != INT) {
        return RET_INVALID_INPUT;
    }
    game_data->level_progression = elem->value.i;
    return copy_skill_three(dico_t_get_any(game_data_file, "skill three"),
        game_data);
}

int init_game_data(window_t *win)
{
    game_data_t *game_data = malloc(sizeof(game_data_t));
    any_t *game_data_file = parse_json_file(GAME_DATA_PATH);
    any_t *font = NULL;

    if (game_data == NULL || game_data_file == NULL ||
        fill_game_data(game_data, game_data_file->value.dict) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    font = dico_t_get_any(game_data_file->value.dict, "font");
    game_data->font = (font != NULL && font->type == STR) ?
        my_strdup(font->value.str) : NULL;
    win->components = dico_t_add_data(win->components, GAME_DATA, game_data,
        destroy_game_data);
    if (win->components == NULL) {
        return RET_INVALID_INPUT;
    }
    destroy_any(game_data_file);
    return RET_OK;
}

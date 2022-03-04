/*
** EPITECH PROJECT, 2022
** defender
** File description:
** load gestion
*/

#include <stdlib.h>
#include "my_strings.h"
#include "defender.h"

static int add_wave(list_ptr_t *load_list)
{
    load_t *load = malloc(sizeof(load_t));

    if (load == NULL) {
        return RET_ERR_MALLOC;
    }
    load->ennemy_file = my_strdup("wave");
    if (load->ennemy_file == NULL) {
        return RET_ERR_MALLOC;
    }
    load->time = 0;
    load->spawn = 0;
    if (list_add_to_end(load_list, load) == NULL) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

static int fill_load_list(char *ennemy_path, any_t *number, any_t *spawn,
    list_ptr_t *load_list)
{
    any_t *ennemy = parse_json_file(ennemy_path);
    any_t *load_time = NULL;
    load_t *load = NULL;

    if (ennemy == NULL || ennemy->type != DICT || number == NULL ||
        number->type != INT || spawn == NULL || spawn->type != INT) {
        return RET_INVALID_INPUT;
    }
    load_time = dico_t_get_any(ennemy->value.dict, "load_time");
    for (int i = 0; i < number->value.i && load_time != NULL; i++) {
        load = malloc(sizeof(load_t));
        if (load == NULL) {
            return RET_ERR_MALLOC;
        }
        load->ennemy_file = ennemy_path;
        printf("load time: %f\n", load_time->value.f);
        if (load_time->type != FLOAT) {
            printf("OUOHO\n");
        }
        load->time = load_time->value.f;
        load->spawn = spawn->value.i;
        list_add_to_end(load_list, load);
    }
    return (load_time != NULL) ? RET_OK : RET_ERR_MALLOC;
}

static int add_data_to_list(any_t *ennemy, any_t *ennemy_file,
    list_ptr_t *load_list)
{
    list_t *elem = NULL;
    char *ennemy_name = NULL;
    any_t *ennemy_path = NULL;

    if (ennemy == NULL || ennemy->type != ARRAY) {
        return RET_INVALID_INPUT;
    }
    elem = ennemy->value.array->start;
    if (my_strcmp(((any_t *) elem->var)->value.str, "wave") == 0) {
        return add_wave(load_list);
    }
    ennemy_name = ((any_t *) elem->var)->value.str;
    ennemy_path = dico_t_get_any(ennemy_file->value.dict, ennemy_name);
    if (ennemy_path == NULL || ennemy_path->type != STR) {
        return RET_ERR_MALLOC;
    }
    return fill_load_list(ennemy_path->value.str, elem->next->var,
        elem->next->next->var, load_list);
}

list_ptr_t *create_load_list(any_t *wave, any_t *ennemy_file)
{
    list_ptr_t *load_list = list_create();
    list_t *elem = NULL;
    any_t *current_wave = NULL;
    int ret = RET_OK;

    if (wave == NULL || wave->type != ARRAY || load_list == NULL ||
        ennemy_file == NULL || ennemy_file->type != DICT) {
        return NULL;
    }
    elem = wave->value.array->start;
    for (int i = 0; i < wave->value.array->len && ret == RET_OK;
        i++, elem = elem->next) {
        current_wave = ((any_t *) elem->var);
        ret = add_data_to_list(current_wave, ennemy_file, load_list);
    }
    return (ret == RET_OK) ? load_list : NULL;
}

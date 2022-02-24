/*
** EPITECH PROJECT, 2022
** json parser
** File description:
** get destroy
*/

#include <stdlib.h>
#include "my_json.h"

void array_destroy(list_ptr_t *array)
{
    list_t *elem = NULL;
    any_t *any = NULL;

    if (array == NULL) {
        return;
    }
    elem = array->start;
    for (int i = 0; i < array->len; i++, elem = elem->next) {
        any = ((any_t *) elem->var);
        destroy_any(any);
    }
}

void destroy_any(void *data)
{
    any_t *any = data;

    if (any == NULL) {
        return;
    }
    switch (any->type) {
        case STR:
            free(any->value.str);
            break;
        case DICT:
            dico_t_destroy(any->value.dict);
            break;
        case ARRAY:
            array_destroy(any->value.array);
            break;
        default:
            break;
    }
}
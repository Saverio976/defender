/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** dup a any_t with malloc
*/

#include <stdlib.h>
#include "my_json.h"

static any_t *fill_any(any_t *any, any_t *new)
{
    if (new == NULL || any == NULL) {
        return (NULL);
    }
    switch (any->type) {
        case STR:
            new->value.str = any->value.str;
        case INT:
            new->value.i = any->value.i;
        case FLOAT:
            new->value.f = any->value.f;
        case ARRAY:
            new->value.array = any->value.array;
        case DICT:
            new->value.dict = any->value.dict;
        default:
            break;
    }
    return (new);
}

any_t *any_dup(any_t *any)
{
    any_t *new = NULL;

    if (any == NULL) {
    }
    new = malloc(sizeof(any_t));
    if (new == NULL) {
        return (NULL);
    }
    new->type = any->type;
    if (fill_any(any, new) == NULL) {
        return (NULL);
    }
    return (new);
}

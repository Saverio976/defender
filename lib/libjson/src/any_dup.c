/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** dup a any_t with malloc
*/

#include <stdlib.h>
#include "my_json.h"

char *rm_space(char const *str)
{
    int char_count = 0;
    char *new = NULL;
    int new_i = 0;

    if (str == NULL) {
        return NULL;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        char_count += (str[i] != ' ') ? 1 : 0;
    }
    new = malloc(sizeof(char) * (char_count + 1));
    for (int i = 0; new != NULL && str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            new[new_i] = str[i];
            new_i += 1;
        }
    }
    return new;
}

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

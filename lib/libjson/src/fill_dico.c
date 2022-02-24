/*
** EPITECH PROJECT, 2022
** json parser
** File description:
** fill dico
*/

#include <stdlib.h>
#include "my_json.h"
#include "my_strings.h"

int create_dico(any_t *any, any_t *key, any_t *value)
{
    if (key != NULL && value != NULL) {
        printf("%p %p %s\n", key, value, key->value.str);
        if (value->type == INT) {
            printf("int %d\n", value->value.i);
        }
        if (value->type == STR) {
            printf("string %s\n", value->value.str);
        }
        if (value->type == DICT) {
            printf("dico\n");
        }
        any->value.dict = dico_t_add_data(any->value.dict,
            my_strdup(key->value.str), value, &destroy_any);
        if (any->value.dict == NULL) {
            return 84;
        }
        key = NULL;
        value = NULL;
    }
    return 0;
}

int fill_dico(list_ptr_t *pile, any_t *any)
{
    list_t *elem = pile->start;
    any_t *cur_any = NULL;
    any_t *key = NULL;
    any_t *value = NULL;
    dico_t *dico = NULL;

    printf("\npile:\n\n");
    for (int i = 0; i < pile->len; i++, elem = elem->next) {
        cur_any = ((any_t *) elem->var);
        printf("boucle\n");
        switch (cur_any->type) {
        case STR:
            printf("str |%s|\n", cur_any->value.str);
        break;
        case INT:
            printf("int |%d|\n", cur_any->value.i);
        break;
        case FLOAT:
            printf("float |%f|\n", cur_any->value.f);
        break;
        case DICT:
            printf("dict\n");
        break;
        case ARRAY:
            printf("array\n");
        break;
        case CHAR:
            printf("char\n");
        default:
            break;
        }
    }
    printf("\nfin pile:\n\n");

    for (int i = 0; i < pile->len; i++, elem = elem->next) {
        cur_any = ((any_t *) elem->var);
        printf("boucle\n");
        if (cur_any->type != CHAR && key == NULL) {
            key = cur_any;
        } else if (cur_any->type != CHAR && key != NULL) {
            value = cur_any;
        }
        if (create_dico(any, key, value) == 84) {
            return 84;
        }
    }
    dico = any->value.dict;
    printf("pute\n");
    printf("key: %s\n", dico->key);
    dico = dico->next;
    printf("key: %s\n", dico->key);
    return 0;
}

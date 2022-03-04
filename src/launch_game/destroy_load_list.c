/*
** EPITECH PROJECT, 2022
** defender
** File description:
** destroy load list
*/

#include <stdlib.h>
#include "defender.h"

void destroy_load_list(void *data)
{
    list_ptr_t *list = data;
    list_t *elem = NULL;
    load_t *load = NULL;

    if (list == NULL) {
        return;
    }
    elem = list->start;
    for (int i = 0; i < list->len; i++, elem = elem->next) {
        load = elem->var;
        free(load->ennemy_file);
        free(load);
    }
    free_list(list);
}

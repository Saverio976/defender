/*
** EPITECH PROJECT, 2022
** LIBLIST
** File description:
** remove elem from list
*/

#include <stdlib.h>
#include "my_dico.h"

int list_t_rem(dico_t *elem)
{
    if (elem == NULL) {
        return (0);
    }
    if (elem->last != NULL) {
        elem->last->next = elem->last;
    }
    if (elem->next != NULL) {
        elem->next->last = elem->last;
    }
    if (elem->destroy != NULL) {
        elem->destroy(elem->value);
    }
    elem->last = NULL;
    elem->next = NULL;
    free(elem);
    return (1);
}
/*
** EPITECH PROJECT, 2022
** defender
** File description:
** ennemy structure fucntions
*/

#include <stdlib.h>
#include "my_json.h"
#include "defender_ennemy.h"

ennemy_t *init_ennemy(any_t *json)
{
    ennemy_t *enn = NULL;

    if (json == NULL) {
        return (NULL);
    }
    enn = malloc(sizeof(ennemy_t));
    return (enn);
}

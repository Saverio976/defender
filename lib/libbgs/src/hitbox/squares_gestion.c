/*
** EPITECH PROJECT, 2022
** defender
** File description:
** squares gestion
*/

#include "my_bgs.h"
#include "my_bgs_components.h"

int squares_handling(char **arr)
{
    sfFloatRect Rect {};

    if (arr == NULL) {
        return BGS_ERR_INPUT;
    }
    while (bsq(arr) == 1) {

    }
    return (BGS_OK);
}
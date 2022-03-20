/*
** EPITECH PROJECT, 2022
** defender
** File description:
** destroy elem
*/

#include <stdlib.h>
#include "defender_game_data.h"

int destroy_elem(float *pos, int *clr, float *scd_pos, int *scdclr)
{
    free(pos);
    free(clr);
    free(scd_pos);
    free(scdclr);
    return RET_OK;
}

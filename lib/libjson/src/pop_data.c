/*
** EPITECH PROJECT, 2022
** json parser
** File description:
** pop data
*/

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "my_json.h"
#include "my_strings.h"
#include "my_conversions.h"

int fill_str(list_ptr_t *pile, any_t *any);
int fill_dico(list_ptr_t *pile, any_t *any);
int fill_array(list_ptr_t *pile, any_t *any);
int fill_nb(list_ptr_t *pile, any_t *any);

static const any_type_t TYPE[] = {STR, INT, ARRAY, DICT};
static int (*FILL_FCT[])(list_ptr_t *, any_t *) = {&fill_str, &fill_nb,
    &fill_array, &fill_dico};

int fill_array(list_ptr_t *pile, any_t *any)
{
    list_t *elem = pile->start;
    any_t *cur_any = NULL;
    any->value.array = list_create();

    if (any->value.array == NULL) {
        return 84;
    }
    for (int i = 0; i < pile->len; i++, elem = elem->next) {
        cur_any = ((any_t *) elem->var);
        if (cur_any->type != CHAR && list_add_to_end(any->value.array,
            cur_any) == NULL) {
            return 84;
        }
    }
    return 0;
}

int fill_nb(list_ptr_t *pile, any_t *any)
{
    any_t any_str = {0};

    if (fill_str(pile, &any_str) == 84) {
        return 84;
    }
    printf("\n\n\n|%s|\n\n\n\n", any_str.value.str);
    if (my_strcontainc(any_str.value.str, '.')) {
        any->type = FLOAT;
        any->value.f = my_atof(any_str.value.str);
    } else {
        any->value.i = my_atoi(any_str.value.str);
        printf("\n\n\n|%d|\n\n\n\n", any->value.i);
    }
    return 0;
}

int fill_str(list_ptr_t *pile, any_t *any)
{
    list_t *elem = pile->start;
    any_t *cur_any = NULL;

    any->value.str = malloc(sizeof(char) * (pile->len + 1));
    if (any->value.str == NULL) {
        return 84;
    }
    any->value.str[pile->len] = '\0';
    for (int i = 0; i < pile->len; i++, elem = elem->next) {
        cur_any = ((any_t *) elem->var);
        if (cur_any->type != CHAR) {
            if (cur_any->type == STR) {
                printf("|%s|\n", cur_any->value.str);
            }
            my_putstr("\n\n\npop data:73 error\n\n");
            return 84;
        }
        any->value.str[i] = cur_any->value.c;
    }
    return 0;
}

int pop_data(list_ptr_t *pile, any_t *any)
{
    int err = 0;

    if (pile == NULL || any == NULL) {
        return 84;
    }
    for (int i = 0; i < 4; i++) {
        if (any->type == TYPE[i]) {
            err = FILL_FCT[i](pile, any);
        }
    }
    return err;
}

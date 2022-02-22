/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** parse
*/

#include "my_bgs.h"
#include "my_fs.h"
#include "my_bgs_components.h"
#include "my_json.h"

bool new_data(char *str, int *id)
{
    if (str[*id] == 34 || str[*id] == '{' || str[*id] == '[' ||
        str[(*id) - 1] == ':') {
        return true;
    }
}

any_type_t fill_data(char origin, char *end, any_t *any)
{
    switch (origin) {
    case 34:
        *end = 34;
        any->type = STR;
    break;
    case '{':
        *end = '}';
        any->type = DICT;
    case '[':
        *end = ']';
        any->type = ARRAY;
    default:
        *end = ',';
        any->type = INT;
    break;
    }
}

any_t *parse_rec(char *str, int *id, list_ptr_t *pile)
{
    char origin = str[*id];
    char end;
    any_t *any = malloc(sizeof(any_t));

    if (any == NULL) {
        return NULL;
    }
    fill_data(origin, &end, any);
    for (; str[*id] != end; *id = *id + 1) {
        if (any->type == INT && str[*id] == '.') {
            any->type = FLOAT;
        }
        if (new_data(str, id) == true) {
            list_add_to_end(pile, parse_rec(str, id, pile));
        }
    }
    
}

dico_t *parse_json(char *file)
{
    int id = 0;
    char *str = fs_get_co;
    any_t *any = NULL;
    dico_t *dico = NULL;
    list_ptr_t *pile = list_create();

    if (pile == NULL || str == NULL) {
        return NULL;
    }    
    list_add_to_end(pile, parse_rec(str, id, pile));
    dico = create_dico_from_any_t(any);
    return;
}
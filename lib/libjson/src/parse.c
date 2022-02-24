/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** parse
*/

#include "my_strings.h"
#include "my_bgs.h"
#include "my_fs.h"
#include "my_bgs_components.h"
#include "my_json.h"
#include "my_puts.h"

bool new_data(char const *str, int *id)
{
    if (*id == 0) {
        return true;
    }
    if (str[(*id) - 1] != '\\' && (str[*id] == 34 || str[*id] == '{' ||
        (str[*id] == ':' && str[*id + 1] >= 48 && str[*id + 1] <= 57) || 
        str[*id] == '[')) {
        return true;
    } else {
        return false;
    }
}

void fill_data(char origin, char *end, any_t *any)
{
    printf("*********\nswitch origin\n");
    switch (origin) {
    case 34:
        *end = 34;
        any->type = STR;
        printf("str\n********\n");
        break;
    case '{':
        *end = '}';
        any->type = DICT;
        printf("dico\n*********\n");
        break;
    case '[':
        *end = ']';
        any->type = ARRAY;
        printf("arr\n**********\n");
        break;
    default:
        *end = ',';
        any->type = INT;
        printf("nb\n************\n");
        break;
    }
}

any_t *parse_rec(char const *str, int *id, int strlen)
{
    char origin = str[*id];
    char end;
    any_t any = {0};
    list_ptr_t *pile = list_create();
    any_t *retany = NULL;

    if (pile == NULL) {
        return NULL;
    }
    fill_data(origin, &end, &any);
    *id = (str[*id] == '\0') ? *id : *id + 1;
    my_printf("id : |%d|\n", *id);
    for (;*id < strlen && str[*id] != end; *id = *id + 1) {
        my_printf("loop c: |%c|\n", str[*id]);
        if (new_data(str, id) == true) {
            list_add_to_end(pile, parse_rec(str, id, strlen));//check retour
        } else if (list_add_to_end(pile, create_any(str[*id])) == NULL) {
            return NULL;
        }
    }
    my_printf("loop end\n\n");
    if (pop_data(pile, &any) == 84) {
        return NULL;
    }
    if (any.type == INT) {
        my_printf("any value %d\n", any.value.i);
    }
    retany = any_dup(&any);
    if (retany == NULL) {
        return NULL;
    }
    printf("***************\nswitch retany\n");
    switch (retany->type) {
    case INT:
        my_printf("ret int: %d\n*************\n", retany->value.i);
    break;
    case STR:
        printf("ret str\n*************\n");
    break;
    case FLOAT:
        printf("ret float\n************\n");
    break;
    case DICT:
        printf("ret dico\n**************\n");
    break;
    case ARRAY:
        printf("ret array\n*************\n");
    break;
    default:
        printf("\n\ndefault\n\n\n");
        break;
    }
    return retany;
}

any_t *parse_json_file(char const path[])
{
    char *str = NULL;

    if (path == NULL) {
        return NULL;
    }
    str = fs_get_content(path);
    if (str == NULL) {
        return NULL;
    }
    return parse_json_str(str);
}

any_t *parse_json_str(char const *str)
{
    int id = 0;
    str = rm_space(str);

    if (str == NULL) {
        return NULL;
    }
    return parse_rec(str, &id, my_strlen(str));
}

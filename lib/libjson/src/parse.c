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

bool new_data(char const *str, int *id)
{
    if (*id == 0) {
        return true;
    }
    if (str[(*id) - 1] != '\\' && (str[*id] == 34 || str[*id] == '{' ||
        str[*id] == '[' || str[(*id) - 1] == ':')) {
        return true;
    } else {
        return false;
    }
}

void fill_data(char origin, char *end, any_t *any)
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

any_t *parse_rec(char const *str, int *id)
{
    char origin = str[*id];
    char end;
    any_t any = {0};
    list_ptr_t *pile = list_create();

    if (pile == NULL) {
        return NULL;
    }
    fill_data(origin, &end, &any);
    *id = (str[*id] == '\0') ? *id : *id + 1;
    my_printf("id : %d\n", *id);
    my_putchar(str[*id]);
    for (; str[*id] != '\0' && str[*id] != end; *id = *id + 1) {
        if (new_data(str, id) == true) {
            list_add_to_end(pile, parse_rec(str, id));
        } else if (list_add_to_end(pile, create_any(str[*id])) == NULL) {
            return NULL;
        }
        my_putchar(str[*id]);
    }
    pop_data(pile, &any);
    return any_dup(&any);
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
    return parse_rec(str, &id);
}

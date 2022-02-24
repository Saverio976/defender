/*
** EPITECH PROJECT, 2022
** json parser
** File description:
** remove space
*/

#include <stdlib.h>
#include <stdbool.h>

static int get_char_nb(char const *str, bool is_in_str)
{
    int ch_nb = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == 34) {
            is_in_str = (is_in_str == true) ? false : true;
        }
        ch_nb += ((str[i] != ' ' || is_in_str == true) && str[i] != '\n') ? 1 : 0;
    }
    return ch_nb;
}

static void check_char(char const *str, int i[], bool is_in_str, char *new)
{
    if ((str[i[0]] != ' ' || is_in_str == true) && str[i[0]] != '\n') {
        new[i[1]] = str[i[0]];
        i[1] = i[1] + 1;
    }
}

char *rm_space(char const *str)
{
    int char_nb = 0;
    char *new = NULL;
    int i[2] = {0, 0};
    bool is_in_str = false;

    if (str == NULL) {
        return NULL;
    }
    char_nb = get_char_nb(str, is_in_str);
    new = malloc(sizeof(char) * (char_nb + 1));
    if (new != NULL) {
        new[char_nb] = '\0';
    }
    for (; new != NULL && str[i[0]] != '\0'; i[0] = i[0] + 1) {
        if (str[i[0]] == 34) {
            is_in_str = (is_in_str == true) ? false : true;
        }
        check_char(str, i, is_in_str, new);
    }
    return new;
}

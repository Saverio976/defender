/*
** EPITECH PROJECT, 2022
** prety print
** File description:
** print dico
*/

#include "my_json.h"
#include "my_puts.h"

int prety_print_rec(any_t *any, int indent);

int close_dico(int indent, int nb)
{
    for (int i = 0; i < indent - 4; i++) {
        nb += my_putchar(' ');
    }
    nb += my_putstr("}");
    return nb;
}

int do_print_dico(any_t *any, int indent)
{
    int nb = 0;
    dico_t *elem = any->value.dict;

    nb += my_putstr("{\n");
    do {
        for (int i = 0; i < indent; i++) {
            nb += my_putchar(' ');
        }
        my_putchar(34);
        my_putstr(elem->key);
        my_putchar(34);
        nb += my_putstr(": ");
        nb += prety_print_rec(elem->value, indent + 4);
        if (elem->next != any->value.dict) {
            nb += my_putchar(',');
        }
        nb += my_putchar('\n');
        elem = elem->next;
    } while (elem != any->value.dict);
    return close_dico(indent, nb);
}

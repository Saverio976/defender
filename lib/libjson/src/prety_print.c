/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** prety print a any_t json
*/

#include <stddef.h>
#include "my_puts.h"
#include "my_dico.h"
#include "my_json.h"
#include "list.h"

static int prety_print_rec(any_t *any, int indent, int need_indent);

static int do_print_dico(any_t *any, int indent)
{
    int nb = 0;
    dico_t *elem = any->value.dict;
    int i = 0;

    nb += my_putstr("{\n");
    do {
        if (i % 2 == 0) {
            nb += prety_print_rec(elem->value, indent + 4, 1);
            nb += my_putstr(": ");
        } else {
            nb += prety_print_rec(elem->value, indent + 4, 0);
            nb += my_putstr(",\n");
        }
        i++;
        elem = elem->next;
    } while (elem != any->value.dict);
    nb += my_putstr("}\n");
    return (nb);
}

static int do_print_array(any_t *any, int indent)
{
    int nb = 0;
    list_t *elem;

    nb += my_putchar('[');
    elem = any->value.array->start;
    for (int i = 0; i < any->value.array->len; i++) {
        nb += prety_print_rec(elem->var, indent, 0);
        if (i != any->value.array->len - 1) {
            nb += my_putstr(", ");
        }
    }
    nb += my_putstr("]");
    return (nb);
}

int my_putfloat(float val)
{
    int entire_parts = (int) val;
    int nb = 0;
    int float_parts = (((int) val) - entire_parts) * 1000000;

    nb += my_putnbr(entire_parts);
    nb += my_putchar('.');
    nb += my_putnbr(float_parts);
    return (nb);
}

static int prety_print_rec(any_t *any, int indent, int need_indent)
{
    int nb = 0;

    for (int i = 0; need_indent && i < indent; i++) {
        nb += my_putchar(' ');
    }
    switch (any->type) {
        case DICT:
            nb += do_print_dico(any, indent);
        case ARRAY:
            nb += do_print_array(any, indent);
        case STR:
            nb += my_printf("\"%s\"", any->value.str);
        case INT:
            nb += my_putnbr(any->value.i);
        case FLOAT:
            nb += my_putfloat(any->value.f);
        default:
            break;
    }
    return (nb);
}

int prety_print(any_t *any)
{
    if (any == NULL) {
        return (0);
    }
    return (prety_print_rec(any, 0, 1));
}

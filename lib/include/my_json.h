/*
** EPITECH PROJECT, 2022
** libjson
** File description:
** lib json header
*/

#ifndef LIBJSON_H_
    #define LIBJSON_H_

    #include "list.h"
    #include "my_dico.h"

enum any_type_e {
    STR,
    INT,
    FLOAT,
    ARRAY,
    DICT
};
typedef enum any_type_e any_type_t;

struct any_s {
    any_type_t type;
    union value_s {
        char *str;
        int i;
        float f;
        list_ptr_t *array;
        dico_t *dict;
    } value;
};
typedef struct any_s any_t;

struct json_s {
    any_t *dico;
    int nb_keys;
};
typedef struct json_s json_t;

// ----------------------------------------------------------------------------

any_t *any_dup(any_t *any);

json_t *parse_json_file(char const path[]);

json_t *parse_json_str(char const *str);

char *rm_space(char const *str);

dico_t *parse_json(char *file);

#endif

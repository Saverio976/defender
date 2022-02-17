/*
** EPITECH PROJECT, 2022
** Defender
** File description:
** add components
*/

#include "my_bgs.h"
#include "my_dico.h"

int object_add_components(object_t *object, void *data, char *key,
    void (*destroy)(void *))
{
    if (object == NULL || data == NULL || key == NULL) {
        return 1;
    }
    object->components = dico_t_add_data(object->components, key, data,
        destroy);
    if (object->components == NULL || object->components->last == NULL) {
        return 84;
    }
    return 0;
}
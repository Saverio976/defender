/*
** EPITECH PROJECT, 2022
** Defender
** File description:
** object set event
*/

#include "my_strings.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "../include/libbgs_private.h"

void my_memcpy(void *dest, int size, void *src)
{
    for (int i = 0; i < size; i++) {
        ((char *) src)[i] = ((char *) dest)[i];
    }
}

int object_set_event(object_t *object, set_event_t *usr_event)
{
    set_event_t *event = NULL;
    char key[255];

    my_strcpy(key, SET_EVENT);
    if (object == NULL || usr_event == NULL) {
        return BGS_ERR_INPUT;
    }
    event = malloc(sizeof(set_event_t));
    if (event == NULL) {
        return BGS_ERR_MALLOC;
    }
    my_memcpy(event, sizeof(set_event_t), usr_event);
    get_id_generator_cat(key);
    dico_t_add_data(object->components, key, event, &free);
    return (BGS_OK);
}

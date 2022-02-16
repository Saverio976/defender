/*
** EPITECH PROJECT, 2022
** defender
** File description:
** object update
*/

#include "my_bgs_components.h"
#include "my_bgs.h"

static const char *KEY_ARR[] = {
    ON_HOVER_KEY,
    ON_RIGHT_KEY,
    ON_LEFT_KEY
};

void object_update(object_t *object, void *scene_data, window_t *win)
{
    void *data = NULL;

    data = dico_t_get_value(object->components, ON_HOVER_KEY);
    if (data != NULL) {
        ((on_hover_t *) data)->hover(object, scene_data, win);
    }
}

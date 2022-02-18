/*
** EPITECH PROJECT, 2022
** defender
** File description:
** object add solid components
*/

#include "my_bgs.h"
#include "my_bgs_components.h"
#include "../include/libbgs_private.h"

static void free_list_abstract(void *list_ptr)
{
    free_list((list_ptr_t *) list_ptr);
}

int scene_add_solid_list(scene_t *scene)
{
    void *value = NULL;

    value = dico_t_get_value(scene->components, ON_COLLISION);
    if (value == NULL) {
        scene->components = dico_t_add_data(scene->components, ON_COLLISION,
            list_create(), &free_list_abstract);
        if (scene->components == NULL) {
            return BGS_ERR_MALLOC;
        }
    }
    return BGS_OK;
}

int object_add_collision(object_t *object, scene_t *scene,
    void (*collision)(object_t *this, object_t *other, dico_t *scene_components,
    window_t *win))
{
    on_collision_t *on_collision = NULL;

    if (object == NULL || scene == NULL) {
        return BGS_ERR_INPUT;
    }
    on_collision = malloc(sizeof(on_collision_t));
    if (on_collision == NULL) {
        return BGS_ERR_MALLOC;
    }
    get_id_generator(on_collision->key);
    on_collision->collision = collision;
    if (scene_add_solid_list(scene) != BGS_OK) {
        return BGS_ERR_MALLOC;
    }
    if (list_add_to_end(dico_t_get_value(scene->components, ON_COLLISION),
        object) == NULL) {
        return BGS_ERR_MALLOC;
    }
    return object_add_components(object, on_collision, ON_COLLISION, &free);
}

/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** add object
*/

#include "my_bgs.h"

int window_add_scene(window_t *win, scene_t *scene)
{
    if (win == NULL || scene == NULL) {
        return 84;
    }
    if (list_add_to_end(win->scenes, scene) == NULL) {
        return 84;
    }
    return 0;
}

int scene_add_object(scene_t *scene, object_t *object)
{
    if (scene == NULL || object == NULL) {
        return 84;
    }
    if (list_add_to_end(scene->objects, object) == NULL) {
        return 84;
    }
    if (object->update != NULL) {
        if (list_add_to_end(scene->updates, object) == NULL) {
            return 84;
        }
    }
    if (object->display != NULL) {
        if (list_add_to_end(scene->displayables, object) == NULL) {
            return 84;
        }
    }
    return 0;
}

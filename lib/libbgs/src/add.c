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
        return BGS_ERR_INPUT;
    }
    if (list_add_to_end(win->scenes, scene) == NULL) {
        return BGS_ERR_MALLOC;
    }
    return BGS_OK;
}

int scene_add_object(scene_t *scene, object_t *object)
{
    if (scene == NULL || object == NULL) {
        return BGS_ERR_INPUT;
    }
    if (object->type == UNSET && list_add_to_end(scene->objects, object) == NULL) {
        return BGS_ERR_MALLOC;
    }
    if (object->update != NULL && object->type == UNSET) {
        if (list_add_to_end(scene->updates, object) == NULL) {
            return BGS_ERR_MALLOC;
        }
    }
    if (object->display != NULL || (object->type == TEXT ||
        object->type == SPRITE)) {
        if (list_add_to_end(scene->displayables, object) == NULL) {
            return BGS_ERR_MALLOC;
        }
    }
    return BGS_OK;
}

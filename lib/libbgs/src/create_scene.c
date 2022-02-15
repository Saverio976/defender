/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** create scene
*/

#include "my_bgs.h"

static int init_list(scene_t *scene)
{
    scene->displayables = list_create();
    if (scene->displayables == NULL) {
        return 84;
    }
    scene->objects = list_create();
    if (scene->objects == NULL) {
        return 84;
    }
    scene->updates = list_create();
    if (scene->updates == NULL) {
        return 84;
    }
    return 0;
}

scene_t *init_scene(void *(*create)(void), void (*destroy)(void *))
{
    scene_t *scene = malloc(sizeof(scene_t));

    if (scene == NULL) {
        return NULL;
    } else if (create == NULL) {
        scene->data = NULL;
    } else {
        scene->data = create();
    }
    scene->destroy = destroy;
    if (init_list(scene) == 84)
        return NULL;
    return scene;
}

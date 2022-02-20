/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** remove
*/

#include <stdlib.h>
#include "my_bgs.h"

static void remove_object(object_t *object)
{
    switch (object->type) {
        case SPRITE:
            sfSprite_destroy(object->drawable.sprite);
            sfTexture_destroy(object->bigdata.sprite_bigdata.texture);
            sfImage_destroy(object->bigdata.sprite_bigdata.image);
            break;
        case TEXT:
            sfText_destroy(object->drawable.text);
            sfFont_destroy(object->bigdata.text_bigdata.font);
            break;
        case AUDIO:
            sfMusic_setLoop(object->drawable.music, sfFalse);
            sfMusic_stop(object->drawable.music);
            sfMusic_destroy(object->drawable.music);
            break;
        default:
            break;
    }
    dico_t_destroy(object->components);
    free(object);
}

static void remove_scene(scene_t *scene)
{
    list_t *elem = scene->objects->start;
    object_t *object = NULL;

    for (int i = 0; i < scene->objects->len; i++) {
        object = ((object_t *) elem->var);
        remove_object(object);
        elem = elem->next;
    }
    if (scene->components != NULL) {
        dico_t_destroy(scene->components);
    }
    free_list(scene->displayables);
    free_list(scene->updates);
    free_list(scene->objects);
    free(scene);
}

void remove_window(window_t *win)
{
    list_t *elem = win->scenes->start;
    scene_t *scene = NULL;

    for (int i = 0; i < win->scenes->len; i++) {
        scene = ((scene_t *) elem->var);
        remove_scene(scene);
        elem = elem->next;
    }
    free_list(win->scenes);
    dico_t_destroy(win->components);
    sfRenderWindow_destroy(win->win);
    free(win);
}
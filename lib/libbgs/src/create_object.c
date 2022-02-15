/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** create object
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_bgs.h"

int object_set_audio(object_t *object, char const *path, bool play_now,
    bool is_loop)
{
    if (object == NULL || path == NULL) {
        return 84;
    }
    object->drawable.music = sfMusic_createFromFile(path);
    if (object->drawable.music) {
        return 84;
    }
    if (play_now == true) {
        sfMusic_play(object->drawable.music);
    }
    if (is_loop == true) {
        sfMusic_setLoop(object->drawable.music, sfTrue);
    }
    object->type = AUDIO;
    return 0;
}

int object_set_cutsom(object_t *object, void *(*create)(void))
{
    if (object == NULL) {
        return 84;
    } else if (create == NULL) {
        object->drawable.custom = NULL;
    } else {
        object->drawable.custom = create();
    }
    object->type = CUSTOM;
    if (object->drawable.custom == NULL) {
        return 1;
    }
    return 0;
}

int object_set_text(object_t *object, char const *path, char const *text)
{
    if (object == NULL || path == NULL || text == NULL) {
        return 84;
    }
    object->bigdata.font = sfFont_createFromFile(path);
    if (object->bigdata.font == NULL) {
        return 84;
    }
    object->drawable.text = sfText_create();
    if (object->drawable.text == NULL) {
        return 84;
    }
    sfText_setFont(object->drawable.text, object->bigdata.font);
    sfText_setString(object->drawable.text, text);
    object->type = TEXT;
    return 0;
}

int object_set_sprite(object_t *object, char const *path)
{
    if (object == NULL || path == NULL) {
        return 84;
    }
    object->bigdata.texture = sfTexture_createFromFile(path, NULL);
    if (object->bigdata.texture == NULL) {
        return 84;
    }
    object->drawable.sprite = sfSprite_create();
    if (object->drawable.sprite == NULL) {
        return 84;
    }
    sfSprite_setTexture(object->drawable.sprite, object->bigdata.texture,
        sfTrue);
    if (object->drawable.sprite == NULL) {
        return 84;
    }
    object->type = SPRITE;
    return 0;
}

object_t *create_object(void *(*create)(void), void (*destroy)(void *),
    void (*update)(object_t *, void *, void *, float),
    void (*display)(object_t *, void *, void *, sfRenderWindow *))
{
    object_t *object = malloc(sizeof(object_t));

    if (object == NULL) {
        return NULL;
    } else if (create == NULL)
        object->data = NULL;
    else {
        object->data = create();
    }
    object->destroy = destroy;
    object->update = update;
    object->display = display;
    return object;
}

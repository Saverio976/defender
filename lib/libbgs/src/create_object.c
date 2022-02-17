/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** create object
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_bgs.h"
#include "../include/libbgs_private.h"

int object_set_audio(object_t *object, char const *path, bool play_now,
    bool is_loop)
{
    if (object == NULL || path == NULL) {
        return BGS_ERR_INPUT;
    }
    object->drawable.music = sfMusic_createFromFile(path);
    if (object->drawable.music == NULL) {
        return BGS_ERR_PATH;
    }
    if (play_now == true) {
        sfMusic_play(object->drawable.music);
    }
    if (is_loop == true) {
        sfMusic_setLoop(object->drawable.music, sfTrue);
    }
    object->type = AUDIO;
    return BGS_OK;
}

int object_set_custom(object_t *object, void *(*create)(void),
    void (*destroy)(void *), char *key)
{
    if (object == NULL || create == NULL || key == NULL) {
        return BGS_ERR_INPUT;
    }
    object->components = dico_t_add_data(object->components, key, create(),
        destroy);
    object->type = CUSTOM;
    return BGS_OK;
}

int object_set_text(object_t *object, char const *path, char const *text,
    scene_t *scene)
{
    if (object == NULL || path == NULL || text == NULL || scene == NULL) {
        return BGS_ERR_INPUT;
    }
    object->bigdata.text_bigdata.display = true;
    object->bigdata.text_bigdata.font = sfFont_createFromFile(path);
    if (object->bigdata.text_bigdata.font == NULL) {
        return BGS_ERR_PATH;
    }
    object->drawable.text = sfText_create();
    if (object->drawable.text == NULL) {
        return BGS_ERR_MALLOC;
    }
    sfText_setFont(object->drawable.text, object->bigdata.text_bigdata.font);
    sfText_setString(object->drawable.text, text);
    object->type = TEXT;
    object->display = &display_text;
    return scene_add_object(scene, object);
}

int object_set_sprite(object_t *object, char const *path, scene_t *scene)
{
    if (object == NULL || path == NULL || scene == NULL) {
        return BGS_ERR_INPUT;
    }
    object->bigdata.sprite_bigdata.display = true;
    object->bigdata.sprite_bigdata.texture =
        sfTexture_createFromFile(path, NULL);
    if (object->bigdata.sprite_bigdata.texture == NULL) {
        return BGS_ERR_PATH;
    }
    object->drawable.sprite = sfSprite_create();
    if (object->drawable.sprite == NULL) {
        return BGS_ERR_MALLOC;
    }
    sfSprite_setTexture(object->drawable.sprite,
        object->bigdata.sprite_bigdata.texture, sfTrue);
    object->type = SPRITE;
    object->display = &display_sprite;
    return scene_add_object(scene, object);
}

object_t *create_object(
    void (*update)(object_t *, dico_t *, window_t *win, float),
    void (*display)(object_t *, dico_t *, dico_t *, sfRenderWindow *),
    scene_t *scene)
{
    object_t *object = malloc(sizeof(object_t));

    if (object == NULL || scene == NULL) {
        return NULL;
    }
    object->bigdata.text_bigdata.font = NULL;
    object->drawable.music = NULL;
    object->components = NULL;
    object->update = update;
    object->display = display;
    object->type = UNSET;
    if (scene_add_object(scene, object) != BGS_OK) {
        return NULL;
    }
    return object;
}

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
    bool loop_now)
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
    if (loop_now == true) {
        sfMusic_setLoop(object->drawable.music, sfTrue);
    }
    object->type = AUDIO;
    return BGS_OK;
}

int object_set_custom(object_t *object)
{
    if (object == NULL) {
        return BGS_ERR_INPUT;
    }
    object->type = CUSTOM;
    return BGS_OK;
}

int object_set_text(object_t *object, char const *path, char const *text)
{
    if (object == NULL || path == NULL || text == NULL) {
        return BGS_ERR_INPUT;
    }
    object->is_visible = true;
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
    object->display = (object->display) ? object->display : &display_text;
    return BGS_OK;
}

int object_set_sprite(object_t *object, char const *path)
{
    if (object == NULL || path == NULL) {
        return BGS_ERR_INPUT;
    }
    object->is_visible = true;
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
    object->display = (object->display) ? object->display : &display_sprite;
    return BGS_OK;
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
    object->is_visible = (display) ? true : false;
    object->type = UNSET;
    if (scene_add_object(scene, object) != BGS_OK) {
        return NULL;
    }
    return object;
}

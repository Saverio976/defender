/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init events for all
*/

#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <stdlib.h>
#include "defender.h"
#include "my_bgs.h"
#include "my_bgs_components.h"

static void event_node_update(object_t *obj,
        __attribute__((unused)) scene_t *scene, window_t *win,
        __attribute__((unused)) set_event_t *evt)
{
    sound_buffer_t *ss = NULL;

    ss = dico_t_get_value(obj->components, "SOUND_CUSTOM_ON");
    if (ss == NULL) {
        return;
    }
    if (sfSound_getStatus(ss->sound) == sfPlaying) {
        sfSound_stop(ss->sound);
    }
    sfSound_play(ss->sound);
    win->click_prev_call = false;
}

static void destroy_sound_custom(void *data)
{
    sound_buffer_t *ss = data;

    if (data == NULL) {
        return;
    }
    sfSound_stop(ss->sound);
    sfSound_destroy(ss->sound);
    sfSoundBuffer_destroy(ss->buffer);
    free(ss);
}

static int set_evt_on(object_t *obj)
{
    sound_buffer_t *ss = NULL;

    ss = malloc(sizeof(sound_buffer_t));
    if (ss == NULL) {
        return (RET_ERR_MALLOC);
    }
    ss->buffer = sfSoundBuffer_createFromFile(
            "./assets/sound/click-effect.ogg");
    if (ss->buffer == NULL) {
        return (RET_ERR_MALLOC);
    }
    ss->sound = sfSound_create();
    if (ss->sound == NULL) {
        return (RET_ERR_MALLOC);
    }
    sfSound_setBuffer(ss->sound, ss->buffer);
    object_add_components(obj, ss, "SOUND_CUSTOM_ON",
            destroy_sound_custom);
    return (RET_OK);
}

int init_events_scoe(object_t *obj)
{
    if (set_evt_on(obj) != RET_OK) {
        return (RET_ERR_MALLOC);
    }
    event_add_node(create_event(event_node_update, false, obj, NULL),
            (node_params_t) {sfMouseLeft, sfKeyA, MOUSE});
    return (RET_OK);
}

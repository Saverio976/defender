/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init music defender
*/

#include "defender_game_data.h"

void update_music(object_t *obj, __attribute__((unused)) scene_t *scene,
    window_t *win, __attribute__((unused)) float time)
{
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);
    sfSoundStatus status;

    if (game_data == NULL) {
        return;
    }
    status = sfMusic_getStatus(obj->drawable.music);
    if (game_data->music == false && status == sfPlaying) {
        sfMusic_stop(obj->drawable.music);
    } else if (status != sfPlaying) {
        sfMusic_play(obj->drawable.music);
    }
}

int set_aud(scene_t *scene, window_t *win)
{
    object_t *audio = create_object(update_music, NULL, scene);
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);

    if (audio == NULL || object_set_audio(audio, AUDIO_PATH,
        game_data->music, true) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    list_add_to_end(scene->updates, audio);
    return RET_OK;
}

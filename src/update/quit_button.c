/*
** EPITECH PROJECT, 2022
** defender
** File description:
** quit button
*/

#include "defender_game_data.h"

void click_quit_level_button(__attribute__((unused)) object_t *obj,
    scene_t *scene, window_t *win, __attribute__((unused)) set_event_t *evt)
{
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);
    object_t *obj_ptr = NULL;

    if (game_data == NULL) {
        return;
    }
    obj_ptr = dico_t_get_value(win->components, MUSIC_OBJ);
    if (obj_ptr != NULL) {
        game_data->music = (game_data->music == true) ? false : true;
        click_music_button(obj_ptr, NULL, win, NULL);
    }
    obj_ptr = dico_t_get_value(win->components, SOUND_OBJ);
    if (obj_ptr != NULL) {
        game_data->sound_effect = (game_data->sound_effect == true) ? false :
            true;
        click_sound_button(obj_ptr, NULL, win, NULL);
    }
    win->scene_index = 1;
    free_list(scene->to_remove);
    scene->to_remove = NULL;
}

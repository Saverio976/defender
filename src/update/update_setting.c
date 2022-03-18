/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update setting
*/

#include "defender.h"
#include "defender_game_data.h"

bool switch_state(bool var, object_t *obj, any_t *any)
{
    any_t *path = NULL;
    bool ret;

    sfTexture_destroy(obj->bigdata.sprite_bigdata.texture);
    if (var == true) {
        ret = false;
        path = dico_t_get_any(any->value.dict, "off path");
    } else {
        ret = true;
        path = dico_t_get_any(any->value.dict, "on path");
    }
    obj->bigdata.sprite_bigdata.texture =
        sfTexture_createFromFile(path->value.str, NULL);
    sfSprite_setTexture(obj->drawable.sprite,
        obj->bigdata.sprite_bigdata.texture, sfTrue);
    return ret;
}

void click_sound_button(object_t *obj, __attribute__((unused)) scene_t *scene,
    window_t *win, __attribute__((unused)) set_event_t *evt)
{
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);
    any_t *any = parse_json_file(SETTING_MENU);

    if (game_data == NULL || any == NULL) {
        return;
    }
    game_data->sound_effect = switch_state(game_data->sound_effect, obj, any);
    destroy_any(any);
}

void click_music_button(object_t *obj, __attribute__((unused)) scene_t *scene,
    window_t *win, __attribute__((unused)) set_event_t *evt)
{
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);
    any_t *any = parse_json_file(SETTING_MENU);

    if (game_data == NULL || any == NULL) {
        return;
    }
    game_data->music = switch_state(game_data->music, obj, any);
    destroy_any(any);
}

void click_back_button(__attribute__((unused)) object_t *obj,
    __attribute__((unused)) scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    win->scene_index = 0;
}

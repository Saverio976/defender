/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update shop error message
*/

#include "defender_game_data.h"

void update_shop_error_message(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win, float dtime)
{
    error_message_data_t *error_message =
        dico_t_get_value(obj->components, "error message");

    if (error_message == NULL) {
        return;
    }
    error_message->frame_counter += 1;
    obj->bigdata.sprite_bigdata.pos.y -= 5;
    if (error_message->frame_counter > 70) {
        list_add_to_end(scene->to_remove, obj);
    }
}

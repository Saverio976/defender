/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create text place error
*/

#include <stdlib.h>
#include "defender_game_data.h"

void update_place_error_message(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) float dtime)
{
    error_message_data_t *error_message =
        dico_t_get_value(obj->components, "place message");

    if (error_message == NULL) {
        return;
    }
    error_message->frame_counter += 1;
    obj->bigdata.text_bigdata.pos.y -= 0.5;
    if (error_message->frame_counter > 70) {
        list_add_to_end(scene->to_remove, obj);
    }
}

bool create_txt_place_err(object_t *support, scene_t *scene, window_t *win)
{
    sfVector2f pos = support->bigdata.sprite_bigdata.pos;
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);
    object_t *text = create_object(update_place_error_message, NULL, scene);
    error_message_data_t *error_message = malloc(sizeof(error_message_data_t));

    if (game_data == NULL || text == NULL || error_message == NULL) {
        return false;
    }
    error_message->frame_counter = 0;
    text->components = dico_t_add_data(text->components, "place message",
        error_message, free);
    pos = (sfVector2f) {pos.x + 60, pos.y + 15};
    object_set_text(text, game_data->font, "bah non enfaite", pos);
    sfText_setCharacterSize(text->drawable.text, 15);
    sfText_setColor(text->drawable.text,
        sfColor_fromRGBA(190, 43, 53, 180));
    list_add_to_end(scene->updates, text);
    list_add_to_end(scene->displayables, text);
    return false;
}

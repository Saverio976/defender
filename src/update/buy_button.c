/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update buy button
*/

#include <stdlib.h>
#include "defender_game_data.h"

object_t *create_error_message(game_data_t *game_data, scene_t *scene,
    sfVector2f pos)
{
    object_t *error_text =
        create_object(update_shop_error_message, NULL, scene);

    pos.x += 60;
    pos.y += 15;
    object_set_text(error_text, game_data->font, "not enough com", pos);
    sfText_setCharacterSize(error_text->drawable.text, 15);
    sfText_setColor(error_text->drawable.text,
        sfColor_fromRGBA(190, 43, 53, 180));
    return error_text;
}

static void fill_error_message_data(error_message_data_t *error_message,
    scene_t *scene)
{
    error_message->obj_list_pos = scene->objects->len;
    error_message->frame_counter = 0;
    error_message->update_list_pos = scene->updates->len;
    error_message->display_list_pos = scene->displayables->len;
}

bool check_money(game_data_t *game_data, dico_t *tower, sfVector2f pos,
    scene_t *scene)
{
    any_t *cost = dico_t_get_any(tower, "cost");
    object_t *error_text = NULL;
    error_message_data_t *error_message = malloc(sizeof(error_message_data_t));

    if (error_message == NULL || cost == NULL || game_data->font == NULL) {
        free(error_message);
        return false;
    } else if (cost->value.i <= game_data->com) {
        game_data->com -= cost->value.i;
        free(error_message);
        return true;
    }
    error_text = create_error_message(game_data, scene, pos);
    fill_error_message_data(error_message, scene);
    list_add_to_end(scene->displayables, error_text);
    list_add_to_end(scene->updates, error_text);
    error_text->components = dico_t_add_data(error_text->components,
        "error message", error_message, free);
    return false;
}

void click_buy_button(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    game_data_t *game_data = dico_t_get_value(win->components, GAME_DATA);
    char *tower_path = dico_t_get_value(obj->components, "tower path");
    any_t *tower = NULL;
    sfFloatRect rect = sfSprite_getGlobalBounds(obj->drawable.sprite);

    if (scene->pause == true || game_data == NULL || tower_path == NULL ||
        obj->is_visible == false) {
        return;
    }
    tower = parse_json_file(tower_path);
    if (tower == NULL || tower->type != DICT ||
        check_money(game_data, tower->value.dict, (sfVector2f) {rect.left +
        (rect.width / 2), rect.top + (rect.height / 2)}, scene) == false) {
        destroy_any(tower);
        return;
    }
    click_shop_button(NULL, scene, NULL, NULL);
    create_drag(scene, win, tower->value.dict, tower_path);
    destroy_any(tower);
}

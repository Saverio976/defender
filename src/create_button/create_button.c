/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create button
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "defender.h"
#include "defender_game_data.h"
#include "my_strings.h"

static void (*button_event[5])(object_t *obj,
        scene_t *scene, window_t *win, set_event_t *evt) = {
    click_play_button,
    click_settings_button,
    click_quit_button,
    click_pause_button,
    click_shop_button
};

void init_button_event(object_t *object, dico_t *dico)
{
    any_t *id = dico_t_get_any(dico, "id");
    any_t *level_path = dico_t_get_any(dico, "level path");

    if (id != NULL && id->type == INT) {
        create_event(on_hover_menu_but, true, object, off_hover_menu_but);
        event_add_node(create_event(button_event[id->value.i], true, object,
            NULL), (node_params_t) {sfMouseLeft , sfKeyA, MOUSE});
    } else if (level_path != NULL && level_path->type == STR) {
        object->components = dico_t_add_data(object->components, "level path",
            my_strdup(level_path->value.str), free);
        event_add_node(create_event(click_level_button, true,
            object, NULL), (node_params_t) {sfMouseLeft , sfKeyA, MOUSE});
    }
}

int init_sprite(float *pos, char *path, scene_t *scene, dico_t *dico)
{
    object_t *sprite = create_object(NULL, NULL, scene);

    if (sprite == NULL || object_set_sprite(sprite, path, (sfIntRect)
        {-1, -1, -1, -1}, (sfVector2f) {pos[1], pos[0]}) != BGS_OK) {
        return RET_INVALID_INPUT;
    }
    init_button_event(sprite, dico);
    check_set_color(sprite, dico);
    return RET_OK;
}

int init_text(float *pos, scene_t *scene, char *arg[2], dico_t *dico)
{
    any_t *size = dico_t_get_any(dico, "size");
    object_t *text = create_object(NULL, NULL, scene);

    if (text == NULL || object_set_text(text, arg[0], arg[1],
        (sfVector2f) {pos[1], pos[0]}) != BGS_OK) {
        return RET_ERR_MALLOC;
    }
    if (size != NULL && size->type == FLOAT) {
        sfText_setScale(text->drawable.text, (sfVector2f) {size->value.f,
            size->value.f});
    }
    check_set_color(text, dico);
    return RET_OK;
}

int get_button_data(scene_t *scene, any_t *dico)
{
    int ret = RET_OK;
    float *txt_pos = get_any_float_array(dico_t_get_any(dico->value.dict,
        "text_pos"));
    float *pos = get_any_float_array(dico_t_get_any(dico->value.dict, "pos"));
    any_t *text = dico_t_get_any(dico->value.dict, "text");
    any_t *sprite_path = dico_t_get_any(dico->value.dict, "sprite path");
    any_t *font_path = dico_t_get_any(dico->value.dict, "font path");
    char *arg[2] = {NULL, NULL};

    if (sprite_path != NULL && pos != NULL) {
        ret = init_sprite(pos, sprite_path->value.str, scene, dico->value.dict);
    }
    if (font_path != NULL && txt_pos != NULL && text != NULL && ret == RET_OK) {
        arg[0] = font_path->value.str;
        arg[1] = text->value.str;
        ret = init_text(txt_pos, scene, arg, dico->value.dict);
    }
    free(txt_pos);
    free(pos);
    return ret;
}

int create_button(scene_t *scene, const char *path)
{
    any_t *any = parse_json_file(path);
    any_t *buttons_array = NULL;
    int ret = RET_OK;

    if (any == NULL) {
        return RET_ERR_MALLOC;
    }
    buttons_array = dico_t_get_any(any->value.dict, "buttons");
    for (int i = 0; buttons_array != NULL && ret == RET_OK &&
        i < buttons_array->value.array->len; i++) {
        ret = get_button_data(scene, get_from_any(any, "da", "buttons", i));
    }
    if (buttons_array == NULL || scene_reload_lists(scene) != RET_OK) {
        ret = RET_ERR_MALLOC;
    }
    destroy_any(any);
    return ret;
}

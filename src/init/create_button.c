/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create button
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my_dico.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "defender.h"
#include "my_strings.h"
#include "my_json.h"

static void (*button_event[4])(object_t *obj,
        scene_t *scene, window_t *win, set_event_t *evt) = {
    click_play_button,
    click_settings_button,
    click_quit_button,
};

void init_button_event(object_t *object, any_t *any,
    __attribute((unused)) scene_t *scene)
{
    any_t *id = dico_t_get_any(any->value.dict, "id");
    any_t *level_path = dico_t_get_any(any->value.dict, "level path");

    create_event(on_hover_menu_but, true, object, off_hover_menu_but);
    if (id != NULL && id->type == INT) {
        event_add_node(create_event(button_event[id->value.i], true, object,
            NULL), (node_params_t) {sfMouseLeft , sfKeyA, MOUSE});
    } else if (level_path != NULL && level_path->type == STR) {
        dico_t_add_data(object->components, "level path",
            my_strdup(level_path->value.str), free);
        event_add_node(create_event(click_level_button, true,
            object, NULL), (node_params_t) {sfMouseLeft , sfKeyA, MOUSE});
    }
}

int init_button(sfVector2f *pos, scene_t *scene, char *path[3], any_t *dico)
{
    object_t *object = NULL;
    any_t *size = dico_t_get_any(dico->value.dict, "size");

    object = create_object(NULL, NULL, scene);
    if (object_set_sprite(object, path[1], (sfIntRect) {-1, -1, -1, -1}, pos[0])
        != BGS_OK) {
        return RET_ERR_MALLOC;
    }
    init_button_event(object, dico, scene);
    object = create_object(NULL, NULL, scene);
    if (object_set_text(object, path[0], path[2], pos[1]) != BGS_OK) {
        return RET_ERR_MALLOC;
    }
    if (size != NULL) {
        sfText_setScale(object->drawable.text, (sfVector2f) {size->value.f,
            size->value.f});
    }
    return RET_OK;
}

int get_button_data(scene_t *scene, any_t *dico, char *path[3])
{
    any_t *text_pos_y = get_from_any(dico, "da", "text_pos", 0);
    any_t *text_pos_x = get_from_any(dico, "da", "text_pos", 1);
    any_t *pos_y = get_from_any(dico, "da", "pos", 0);
    any_t *pos_x = get_from_any(dico, "da", "pos", 1);
    any_t *text = get_from_any(dico, "d", "text");

    if (text_pos_y == NULL || text_pos_x == NULL || pos_y == NULL ||
        pos_x == NULL || text == NULL) {
        return RET_ERR_MALLOC;
    }
    path[2] = text->value.str;
    return init_button((sfVector2f[]) {{pos_x->value.f, pos_y->value.f},
        {text_pos_x->value.f, text_pos_y->value.f}}, scene, path, dico);
}

int get_path(dico_t *dico, char *tab[3])
{
    any_t *font_any = dico_t_get_any(dico, "font path");
    any_t *sprite_any = dico_t_get_any(dico, "sprite path");

    if (font_any == NULL || sprite_any == NULL) {
        return RET_ERR_MALLOC;
    }
    tab[0] = font_any->value.str;
    tab[1] = sprite_any->value.str;
    return RET_OK;
}

int create_button(scene_t *scene, const char *path)
{
    any_t *any = parse_json_file(path);
    any_t *buttons_array = NULL;
    char *tab[3] = {NULL, NULL};
    int ret = RET_OK;

    if (any == NULL || get_path(any->value.dict, tab)
        != RET_OK) {
        return RET_ERR_MALLOC;
    }
    buttons_array = dico_t_get_any(any->value.dict, "buttons");
    for (int i = 0; buttons_array != NULL && ret == RET_OK &&
        i < buttons_array->value.array->len; i++) {
        ret = get_button_data(scene,
            get_from_any(any, "da", "buttons", i), tab);
    }
    destroy_any(any);
    return (buttons_array) ? ret : RET_INVALID_INPUT;
}

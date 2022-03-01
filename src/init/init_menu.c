/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "my_dico.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "defender.h"
#include "my_json.h"

int create_button(sfVector2f text_pos, sfVector2f pos, scene_t *scene,
    char *path[3])
{
    object_t *object = NULL;

    object = create_object(NULL, NULL, scene);
    if (object_set_sprite(object, path[1], (sfIntRect) {-1, -1, -1, -1}, pos)
        != BGS_OK) {
        return RET_ERR_MALLOC;
    }
    create_event(on_hover_menu_but, true, object, off_hover_menu_but);
    object = create_object(NULL, NULL, scene);
    if (object_set_text(object, path[0], path[2], text_pos)
        != BGS_OK) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

int init_button(scene_t *scene, any_t *any, int i, char *path[3])
{
    any_t *text_pos_y = get_from_any(any, "dada", "buttons", i, "text_pos", 0);
    any_t *text_pos_x = get_from_any(any, "dada", "buttons", i, "text_pos", 1);
    any_t *pos_y = get_from_any(any, "dada", "buttons", i, "pos", 0);
    any_t *pos_x = get_from_any(any, "dada", "buttons", i, "pos", 1);
    any_t *text = get_from_any(any, "dad", "buttons", i, "text");

    if (text_pos_y == NULL || text_pos_x == NULL || pos_y == NULL ||
        pos_x == NULL || text == NULL) {
        return RET_ERR_MALLOC;
    }
    path[2] = text->value.str;
    if (create_button((sfVector2f) {text_pos_x->value.f, text_pos_y->value.f},
        (sfVector2f) {pos_x->value.f, pos_y->value.f}, scene,
        path) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return (RET_OK);
}

int get_path(dico_t *dico, char **font_path, char **sprite_path)
{
    any_t *font_any = dico_t_get_any(dico, "font_path");
    any_t *sprite_any = dico_t_get_any(dico, "sprite_path");

    if (font_path == NULL || sprite_path == NULL) {
        return RET_ERR_MALLOC;
    }
    *font_path = font_any->value.str;
    *sprite_path = sprite_any->value.str;
    return RET_OK;
}

int init_menu(window_t *win)
{
    int ret = RET_OK;
    any_t *any = parse_json_file(MAIN_MENU);
    scene_t *scene = create_scene(win, sfBlack);
    char *sprite_path = NULL;
    char *font_path = NULL;
    char *tab[3] = {NULL, NULL};

    if (any == NULL || get_path(any->value.dict, &font_path,
        &sprite_path) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    tab[0] = font_path;
    tab[1] = sprite_path;
    for (int i = 0; i < 3 && ret == RET_OK; i++) {
        ret = init_button(scene, any, i, tab);
    }
    destroy_any(any);
    return ret;
}

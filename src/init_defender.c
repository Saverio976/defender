/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init defender
** defender
*/

#include <SFML/Graphics.h>
#include <stddef.h>
#include <stdlib.h>
#include "defender.h"
#include "my_bgs.h"
#include "my_json.h"

sfVector2f *read_pos(dico_t *dico)
{
    any_t *text_pos = NULL;
    any_t *pos = NULL;
    sfVector2f *vector = malloc(sizeof(sfVector2f) * 2);
    list_ptr_t *array = NULL;

    if (vector == NULL) {
        return NULL;
    }
    text_pos = dico_t_get_any(dico, "text_pos");
    pos = dico_t_get_any(dico, "pos");
    if (text_pos == NULL || pos == NULL) {
        return NULL;
    }
    array = text_pos->value.array;
    pos = ((any_t *) array->start)
}

int init_button(scene_t *scene, char *sprite_path, char *font_path,
    dico_t *dico)
{
    object_t *object = NULL;
    sfVector2f *pos = read_pos(dico);

    object = create_object(NULL, NULL, scene);
    object_set_sprite(object, sprite_path, (sfIntRect) {0},
        );
}

int get_path(dico_t *dico, const char **font_path, list_ptr_t **array,
    const char **sprite_path)
{
    any_t *font_any = dico_t_get_any(dico, "font_path")->value.str;
    any_t *array_any = dico_t_get_any(dico, "buttons")->value.array;
    any_t *sprite_any = dico_t_get_any(dico, "sprite_path")->value.str;

    if (font_path == NULL || array == NULL || sprite_path == NULL) {
        return RET_ERR_MALLOC;
    }
    *font_path = font_any->value.str;
    *array = array_any->value.array;
    *sprite_path = sprite_any->value.str;
    return RET_OK;
}

int init_menu(window_t *win)
{
    any_t *any = parse_json_file(MAIN_MENU);
    scene_t *scene = create_scene(win, sfBlack);
    object_t *object = NULL;
    char *sprite_path = NULL;
    char *font_path = NULL;
    list_ptr_t *array = NULL;
    list_t *elem = NULL;

    if (any == NULL || get_path(any->value.dict, &font_path, &array,
        &sprite_path) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    elem = array->start;
    for (int i = 0; i < 3; i++, elem = elem->next) {
        if (init_button(scene, sprite_path, font_path,
            ((dico_t *) elem->var)) != RET_OK) {
            return RET_ERR_MALLOC;
        }
    }
    return RET_OK;
}

int init_defender(int ac, char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    char const title[] = "DEFENDER";
    sfUint32 style = {0};
    window_t *win = create_window(mode, title, style);

    if (win == NULL || init_menu(win) != RET_OK) {
        RET_ERR_MALLOC;
    }
    return RET_OK;
}
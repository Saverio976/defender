/*
** EPITECH PROJECT, 2022
** defender
** File description:
** end game
*/

#include <stdlib.h>
#include "defender_game_data.h"

static object_t *create_elem(scene_t *scene, int *clr, float *pos, char *path)
{
    object_t *elem = NULL;

    if (clr == NULL || pos == NULL || path == NULL) {
        return NULL;
    }
    elem = create_object(NULL, NULL, scene);
    if (elem == NULL || object_set_sprite(elem, path, (sfIntRect)
        {-1, -1, -1, -1}, (sfVector2f) {pos[0], pos[1]}) != RET_OK) {
        return NULL;
    }
    sfSprite_setColor(elem->drawable.sprite, sfColor_fromRGBA(clr[0],
        clr[1], clr[2], clr[3]));
    list_add_to_end(scene->displayables, elem);
    return elem;
}

static void set_elem_event(object_t *obj, scene_t *scene)
{
    if (obj == NULL) {
        return;
    }
    create_event(on_hover_menu_but, true, obj, off_hover_menu_but);
    event_add_node(create_event(NULL, true, obj, click_quit_level_button),
        (node_params_t) {sfMouseLeft , sfKeyA, MOUSE});
    list_add_to_end(scene->updates, obj);
}

static int create_menu(scene_t *scene, dico_t *end, any_t *f)
{
    int *clr = get_any_int_array(dico_t_get_any(end, "back color"));
    float *pos = get_any_float_array(dico_t_get_any(end, "back pos"));
    any_t *bck_pth = dico_t_get_any(end, "back path");
    int *btn_clr = get_any_int_array(dico_t_get_any(end, "color"));
    any_t *b_p = dico_t_get_any(end, "button path");
    float *b_pos = get_any_float_array(dico_t_get_any(end, "button pos"));
    any_t *t = dico_t_get_any(end, "button text");
    object_t *txt = create_object(NULL, NULL, scene);

    if (clr == NULL || b_pos == NULL || t == NULL || f == NULL || txt == NULL) {
        return RET_ERR_MALLOC;
    }
    create_elem(scene, clr, pos, bck_pth->value.str);
    set_elem_event(create_elem(scene, btn_clr, b_pos, b_p->value.str), scene);
    object_set_text(txt, f->value.str, t->value.str,
        (sfVector2f) {b_pos[0], b_pos[1]});
    sfText_setColor(txt->drawable.text,
        sfColor_fromRGBA(clr[0], clr[1], clr[2], clr[3]));
    list_add_to_end(scene->displayables, txt);
    return destroy_elem(pos, btn_clr, b_pos, clr);
}

static void set_text(object_t *text, sfVector2f pos, dico_t *end, bool win)
{
    any_t *size = dico_t_get_any(end, "size");
    any_t *path = dico_t_get_any(end, "font path");
    int *clr = get_any_int_array(dico_t_get_any(end, "color"));

    if (size == NULL || path == NULL || clr == NULL) {
        return;
    }
    if (win == true) {
        if (object_set_text(text, path->value.str, "you win", pos) != RET_OK) {
            return;
        }
    } else {
        if (object_set_text(text, path->value.str, "you lose", pos) != RET_OK) {
            return;
        }
    }
    sfText_setColor(text->drawable.text,
        sfColor_fromRGBA(clr[0], clr[1], clr[2], clr[3]));
    sfText_setCharacterSize(text->drawable.text, size->value.i);
    free(clr);
}

void end_game(scene_t *scene, bool win)
{
    any_t *end = parse_json_file(END_MENU);
    float *pos = NULL;
    object_t *text = create_object(NULL, NULL, scene);

    if (scene->updates == NULL || end == NULL || text == NULL ||
        create_menu(scene, end->value.dict,
        dico_t_get_any(end->value.dict, "font path")) != RET_OK) {
        return;
    }
    scene->pause = true;
    pos = get_any_float_array(dico_t_get_any(end->value.dict, "text pos"));
    if (pos == NULL) {
        return;
    }
    set_text(text, (sfVector2f) {pos[0], pos[1]}, end->value.dict, win);
    list_add_to_end(scene->displayables, text);
    free(pos);
    destroy_any(end);
}

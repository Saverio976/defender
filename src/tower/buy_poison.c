/*
** EPITECH PROJECT, 2022
** defender
** File description:
** buy poison
*/

#include <stdlib.h>
#include "my_strings.h"
#include "defender_game_data.h"

static void create_poison(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt)
{
    object_t *poison = NULL;
    poison_t *data = dico_t_get_value(obj->components, "data");
    char *path = dico_t_get_value(obj->components, "path");
    sprite_bigdata_t dat = obj->bigdata.sprite_bigdata;

    if (check_drag_pos(win, 4) == false || data == NULL || path == NULL)
        return;
    poison = create_object(update_poison, display_poison, scene);
    if (object_set_sprite(poison, path, dat.rect, dat.pos) != RET_OK) {
        return;
    }
    poison->components = dico_t_add_data(poison->components, "data", data,
        destroy_poison_data);
    sfCircleShape_setPosition(data->scope, obj->bigdata.sprite_bigdata.pos);
    add_to_poison_list(scene, poison);
    list_add_to_i(scene->displayables, poison,
        (int) dico_t_get_value(scene->components, ENNEMY_ID));
    list_add_to_end(scene->updates, poison);
    list_add_to_end(scene->to_remove, obj);
}

static sfCircleShape *set_circle(float rad)
{
    sfCircleShape *circle = sfCircleShape_create();

    if (circle == NULL) {
        return NULL;
    }
    sfCircleShape_setOrigin(circle, (sfVector2f) {rad, rad});
    sfCircleShape_setFillColor(circle, sfColor_fromRGBA(129, 21, 77, 150));
    sfCircleShape_setRadius(circle, rad);
    return circle;
}

static int set_poison_data(dico_t *poison, object_t *drag)
{
    any_t *time = dico_t_get_any(poison, "time");
    any_t *scope = dico_t_get_any(poison, "scope");
    poison_t *data = malloc(sizeof(poison_t));

    if (time == NULL || scope == NULL || data == NULL) {
        return RET_ERR_MALLOC;
    }
    data->scope_rad = scope->value.i * 40;
    data->timer = time->value.i;
    data->scope = set_circle(data->scope_rad);
    drag->components = dico_t_add_data(drag->components, "data", data,
        NULL);
    if (data->scope == NULL || drag->components == NULL) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

static void set_poison_drag(scene_t *scene, dico_t *poison, sfVector2f pos)
{
    object_t *drag = create_object(update_drag, NULL, scene);
    any_t *path = dico_t_get_any(poison, "path");

    if (drag == NULL || path == NULL || object_set_sprite(drag, path->value.str,
        (sfIntRect) {-1, -1, -1, -1}, pos) != RET_OK ||
        event_add_node(create_event(create_poison, true, drag, NULL),
        (node_params_t) {sfMouseLeft, sfKeyA, MOUSE}) != RET_OK) {
        return;
    }
    drag->components = dico_t_add_data(drag->components, "path",
        my_strdup(path->value.str), free);
    if (drag->components == NULL || set_poison_data(poison, drag) != RET_OK) {
        return;
    }
    list_add_to_end(scene->updates, drag);
    list_add_to_end(scene->displayables, drag);
}

void buy_poison(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
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
    set_poison_drag(scene, tower->value.dict, obj->bigdata.sprite_bigdata.pos);
    destroy_any(tower);
}

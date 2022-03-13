/*
** EPITECH PROJECT, 2022
** defender
** File description:
** set tower scope
*/

#include "defender_game_data.h"

int create_scope(scene_t *scene, sfIntRect current_rect, sfVector2f pos,
    sfColor color)
{
    object_t *obj = NULL;

    obj = create_object(NULL, NULL, scene);
    if (object_set_sprite(obj, SCOPE_PATH, current_rect, pos) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    obj->is_visible = false;
    sfSprite_setColor(obj->drawable.sprite, color);
    if (list_add_to_end(scene->displayables, obj) == NULL) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

int place_scope(sfVector2f size, sfIntRect current_rect, sfVector2f pos, scene_t
    *scene)
{
    int ret = RET_OK;
    sfColor color = sfColor_fromRGBA(SCOPE_RGBA[0], SCOPE_RGBA[1],
        SCOPE_RGBA[2], SCOPE_RGBA[3]);

    for (int i = 0; i < (size.x * 2) + size.y && ret == RET_OK; i++) {
        if (ret == RET_OK && (i < size.x || i > size.x + size.y - 1)) {
            ret = create_scope(scene, current_rect, pos, color);
        }
        pos.y += SQUARE_POS_INCREMENTATION;
        if (ret == RET_OK && i < size.x) {
            current_rect.width += (SQUARE_POS_INCREMENTATION * 2);
        } else if (ret == RET_OK && i > size.x + size.y - 2) {
            current_rect.width -= (SQUARE_POS_INCREMENTATION * 2);
        }
    }
    return ret;
}

int place_side_scope(scene_t *scene, int scope, int size,
    sfFloatRect support_rect)
{
    sfVector2f pos = {support_rect.left -
        (SQUARE_POS_INCREMENTATION * (scope / 2)), support_rect.top +
        (SQUARE_POS_INCREMENTATION * (size / 2))};
    sfIntRect rect = {0, 0, scope * SQUARE_POS_INCREMENTATION,
        SQUARE_POS_INCREMENTATION * size};
    sfColor color = sfColor_fromRGBA(SCOPE_RGBA[0], SCOPE_RGBA[1],
        SCOPE_RGBA[2], SCOPE_RGBA[3]);

    if (create_scope(scene, rect, pos, color) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    pos.x = support_rect.left + (size * SQUARE_POS_INCREMENTATION) +
        (SQUARE_POS_INCREMENTATION * (scope / 2));
    if (create_scope(scene, rect, pos, color) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

int fill_scope_list(sfFloatRect support_rect, scene_t *scene, int scope,
    int size)
{
    sfVector2f pos = {support_rect.left + (SQUARE_POS_INCREMENTATION *
        (size / 2)), support_rect.top + SQUARE_START_POS -
        (scope * SQUARE_POS_INCREMENTATION)};
    sfIntRect current_rect = {0, 0, SQUARE_POS_INCREMENTATION * size,
        SQUARE_POS_INCREMENTATION};

    if (place_side_scope(scene, scope, size, support_rect) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return place_scope((sfVector2f) {scope, size}, current_rect, pos, scene);
}

int set_scope(dico_t *tower_dico, dico_t *components[2], object_t *support,
    scene_t *scene)
{
    tower_data_t *tower_data = dico_t_get_value(components[0], TOWER_DATA);
    any_t *scope = dico_t_get_any(tower_dico, "scope");
    any_t *size = dico_t_get_any(tower_dico, "size");
    list_t *elem = scene->objects->end;

    if (tower_data == NULL || scope == NULL || size == NULL ||
        dico_t_add_data(components[1], TOWER_DATA, tower_data, NULL) == NULL) {
        return RET_INVALID_INPUT;
    }
    tower_data->scope = list_create();
    if (tower_data->scope == NULL ||
        fill_scope_list(sfSprite_getGlobalBounds(support->drawable.sprite),
        scene, scope->value.i, size->value.i) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    while (elem != scene->objects->end) {
        elem = elem->next;
        list_add_to_end(tower_data->scope, elem->var);
    }
    return RET_OK;
}

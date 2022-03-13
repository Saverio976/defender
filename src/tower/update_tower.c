/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update tower
*/

#include "defender_game_data.h"

void shot_ennemy(sfFloatRect intersection, object_t *tower)
{
    my_putstr("shot ennemy\n");
}

sfFloatRect check_scope_col(sfFloatRect scope_rect, list_ptr_t *ennemy_list)
{
    list_t *elem = NULL;
    object_t *ennemy = NULL;
    sfFloatRect ennemy_rect;
    sfFloatRect intersection;

    if (ennemy_list == NULL || ennemy_list->len == 0 ||
        ennemy_list->start == NULL) {
        return (sfFloatRect) {-1, -1, -1, -1};
    }
    elem = ennemy_list->start;
    for (int i = 0; i < ennemy_list->len; i++, elem = elem->next) {
        ennemy = elem->var;
        ennemy_rect = sfSprite_getGlobalBounds(ennemy->drawable.sprite);
        if (sfFloatRect_intersects(&scope_rect, &ennemy_rect,
            &intersection) == sfTrue) {
            return intersection;
        }
    }
    return (sfFloatRect) {-1, -1, -1, -1};
}

bool detect_ennemy(tower_data_t *tower_data, list_ptr_t *ennemy_list,
    object_t *tower)
{
    list_t *elem = NULL;
    sfFloatRect intersection;
    object_t *obj = NULL;

    if (tower_data->scope == NULL || tower_data->scope->len == 0 ||
        tower_data->scope->start == NULL) {
        return false;
    }
    elem = tower_data->scope->start;
    for (int i = 0; i < tower_data->scope->len; i++, elem = elem->next) {
        obj = elem->var;
        intersection = check_scope_col(
            sfSprite_getGlobalBounds(obj->drawable.sprite), ennemy_list);
        if (intersection.left != -1) {
            shot_ennemy(intersection, tower);
            return true;
        }
    }
    return false;
}

void update_tower(object_t *obj, scene_t *scene, window_t *win, float time)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);
    list_ptr_t *ennemy_list = dico_t_get_value(scene->components,
        "ennemy list");

    if (tower_data == NULL || ennemy_list == NULL) {
        return;
    }
    if (detect_ennemy(tower_data, ennemy_list, obj) == false) {
        sfSprite_rotate(obj->drawable.sprite, TOWER_ROTATION);
    }
    return;
}

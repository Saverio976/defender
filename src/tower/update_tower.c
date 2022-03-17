/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update tower
*/

#include "defender_game_data.h"
#include "defender_ennemy.h"
#include "my_bgs.h"

object_t *check_scope_col(sfFloatRect scope_rect, list_ptr_t *ennemy_list)
{
    list_t *elem = NULL;
    object_t *ennemy = NULL;
    sfFloatRect ennemy_rect;
    sfFloatRect intersection;

    if (ennemy_list == NULL || ennemy_list->len == 0 ||
        ennemy_list->start == NULL) {
        return NULL;
    }
    elem = ennemy_list->start;
    for (int i = 0; i < ennemy_list->len; i++, elem = elem->next) {
        ennemy = elem->var;
        ennemy_rect = sfSprite_getGlobalBounds(ennemy->drawable.sprite);
        if (sfFloatRect_intersects(&scope_rect, &ennemy_rect,
            &intersection) == sfTrue && ennemy->is_visible == true) {
            return ennemy;
        }
    }
    return (NULL);
}

bool detect_ennemy(tower_data_t *tower_data, list_ptr_t *ennemy_list,
    object_t *tower, scene_t *scene)
{
    list_t *elem = NULL;
    object_t *obj = NULL;
    object_t *obj_enn = NULL;

    if (tower_data->scope == NULL || tower_data->scope->len == 0 ||
        tower_data->scope->start == NULL) {
        return false;
    }
    elem = tower_data->scope->start;
    for (int i = 0; i < tower_data->scope->len; i++, elem = elem->next) {
        obj = elem->var;
        obj_enn = check_scope_col(
            sfSprite_getGlobalBounds(obj->drawable.sprite), ennemy_list);
        if (obj_enn != NULL) {
            shot_ennemy(obj_enn, tower, tower_data, scene);
            return true;
        }
    }
    return false;
}

void update_tower(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, __attribute__((unused)) float time)
{
    tower_data_t *tower_data = dico_t_get_value(obj->components, TOWER_DATA);
    list_ptr_t *ennemy_list = dico_t_get_value(scene->components,
        LIST_ENNEMY);

    if (tower_data == NULL || ennemy_list == NULL || scene->pause == true) {
        return;
    }
    tower_data->dtime += time;
    if (detect_ennemy(tower_data, ennemy_list, obj, scene) == false) {
        sfSprite_rotate(obj->drawable.sprite, TOWER_ROTATION);
    }
    return;
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update tower
*/

#include "stdlib.h"
#include "defender_game_data.h"
#include "defender_ennemy.h"
#include "my_bgs.h"

static bool check_col(object_t *ennemy, sfVector2f circle, float rad)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(ennemy->drawable.sprite);
    sfVector2f distance = {abs(circle.x - rect.left), abs(circle.y - rect.top)};
    sfVector2f corner = {distance.x - rect.width / 2,
        distance.y - rect.height / 2};
    float corner_distance_sq = 0;

    if ((distance.x > (rect.width / 2 + rad)) ||
        (distance.y > (rect.height / 2 + rad))) {
        return false;
    } else if ((distance.x <= rect.width / 2) ||
        (distance.x <= rect.height / 2)) {
        return true;
    }
    corner_distance_sq = ((corner.x * corner.x) + (corner.y * corner.y));
    if (corner_distance_sq <= (rad * rad)) {
        return true;
    }
    return false;
}

static bool check_type(object_t *ennemy, int tower_type)
{
    ennemy_t *data = dico_t_get_value(ennemy->components, OBJ_COMP_ENNSTRUCT);
    int var;

    if (data == NULL) {
        return false;
    } else if (tower_type == 2) {
        return true;
    }
    var = (data->is_fly == true) ? 1 : 0;
    return (tower_type == var) ? true : false;
}

static object_t *check_scope_col(sfVector2f circle, list_ptr_t *ennemy_list,
    float rad, int tower_type)
{
    list_t *elem = NULL;

    if (ennemy_list == NULL || ennemy_list->len == 0 ||
        ennemy_list->start == NULL) {
        return NULL;
    }
    elem = ennemy_list->start;
    for (int i = 0; i < ennemy_list->len; i++, elem = elem->next) {
        if (check_type(elem->var, tower_type) == true &&
            check_col(elem->var, circle, rad) == true) {
            return elem->var;
        }
    }
    return NULL;
}

static bool detect_ennemy(tower_data_t *tower_data, list_ptr_t *ennemy_list,
    object_t *tower, scene_t *scene)
{
    object_t *ennemy = NULL;
    sfVector2f pos = sfCircleShape_getPosition(tower_data->scope);

    if (tower_data->scope == NULL) {
        return false;
    }
    ennemy = check_scope_col(pos, ennemy_list, tower_data->scope_rad,
        tower_data->fly);
    if (ennemy != NULL) {
        shot_ennemy(ennemy, tower, tower_data, scene);
        return true;
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

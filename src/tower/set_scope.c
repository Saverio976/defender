/*
** EPITECH PROJECT, 2022
** defender
** File description:
** set tower scope
*/

#include "defender_game_data.h"

static int init_circle(sfVector2f pos, tower_data_t *tower_data)
{
    sfCircleShape_setPosition(tower_data->scope, pos);
    sfCircleShape_setRadius(tower_data->scope, tower_data->scope_rad);
    sfCircleShape_setFillColor(tower_data->scope, sfColor_fromRGBA(
        SCOPE_RGBA[0], SCOPE_RGBA[1], SCOPE_RGBA[2], SCOPE_RGBA[3]));
    sfCircleShape_setOrigin(tower_data->scope,
        (sfVector2f) {tower_data->scope_rad, tower_data->scope_rad});
    return RET_OK;
}

int set_scope(dico_t *components[2], object_t *support)
{
    tower_data_t *tower_data = dico_t_get_value(components[0], TOWER_DATA);

    if (tower_data == NULL || dico_t_add_data(components[1], TOWER_DATA,
        tower_data, NULL) == NULL) {
        return RET_INVALID_INPUT;
    }
    tower_data->scope = sfCircleShape_create();
    tower_data->scope_display = false;
    if (tower_data->scope == NULL || init_circle(sfSprite_getPosition(support->
        drawable.sprite), tower_data) != RET_OK) {
        return RET_ERR_MALLOC;
    }
    return RET_OK;
}

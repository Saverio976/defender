/*
** EPITECH PROJECT, 2022
** defender
** File description:
** set tower scope
*/

#include "defender_game_data.h"

int fill_cope_list(sfFloatRect support_rect, scene_t *scene, int scope,
    int size)
{
    sfVector2f pos = {support_rect.left + (SQUARE_POS_INCREMENTATION *
        (size / 2)), support_rect.top + SQUARE_START_POS -
        (scope * SQUARE_POS_INCREMENTATION)};
    sfFloatRect current_rect = {0, 0, SQUARE_POS_INCREMENTATION,
        SQUARE_POS_INCREMENTATION * size};

    //faire un rectangle par ligne ou un carre par case
    //un carre par case apporte une precision de detection quoiquon a deja le rect de l'ennemi rentrant dans le scope
    for (int i = 0; i < scope * 2 + size; i++) {
        create_scope(current_rect, pos, scene);
        pos.y += SQUARE_POS_INCREMENTATION;

    }
    
}

int set_scope(dico_t *tower_dico, dico_t *tower_components, object_t *support,
    scene_t *scene)
{
    tower_data_t *tower_data = dico_t_get_value(tower_components, TOWER_DATA);
    any_t *scope = dico_t_get_any(tower_dico, "scope");
    any_t *size = dico_t_get_any(tower_dico, "size");

    if (tower_data == NULL || scope == NULL || size == NULL) {
        return RET_INVALID_INPUT;
    }
    tower_data->scope = list_create();
    if (tower_data->scope == NULL) {
        return RET_ERR_MALLOC;
    }
    return fill_scope_list(sfSprite_getGlobalBounds(support->drawable.sprite),
        scene, scope->value.i, size->value.i);
}

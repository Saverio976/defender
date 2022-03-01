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

int init_level_menu(window_t *win)
{
    scene_t *scene = create_scene(win, sfBlack);
    object_t *background = NULL;
    any_t *any = parse_json_file(LEVEL_MENU);

    if (scene == NULL || any == NULL) {
        return RET_ERR_MALLOC;
    }
    any = dico_t_get_any(any->value.dict, "background path");
    background = create_object(NULL, NULL, scene);
    if (background == NULL) {
        return RET_ERR_MALLOC;
    }
    if (any != NULL) {
        if (object_set_sprite(background, any->value.str,
            (sfIntRect) {-1, -1, -1, -1}, (sfVector2f) {960, 540}) != BGS_OK) {
            return RET_INVALID_INPUT;
        }
    }
    return create_button(scene, LEVEL_MENU);
}

int init_main_menu(window_t *win)
{
    scene_t *scene = create_scene(win, sfBlack);

    if (scene == NULL) {
        return RET_ERR_MALLOC;
    }
    return create_button(scene, MAIN_MENU);
}

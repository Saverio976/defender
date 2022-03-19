/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create all texts drawable in game
*/

#include "my_bgs.h"
#include "defender.h"
#include "defender_ennemy.h"
#include "defender_game_data.h"

static int create_texts_life(scene_t *scene)
{
    object_t *obj = NULL;

    obj = create_object(update_draw_life, NULL, scene);
    if (obj == NULL) {
        return (RET_ERR_MALLOC);
    }
    if (object_set_text(obj, "assets/font/menlo.ttf", "life",
                (sfVector2f) {1500, 10}) != BGS_OK) {
        return (RET_ERR_MALLOC);
    }
    list_add_to_end(scene->updates, obj);
    list_add_to_end(scene->displayables, obj);
    return (RET_OK);
}

static int create_texts_score(scene_t *scene)
{
    object_t *obj = NULL;

    obj = create_object(update_score_total_text, NULL, scene);
    if (obj == NULL) {
        return (RET_ERR_MALLOC);
    }
    if (object_set_text(obj, "./assets/font/menlo.ttf", "",
                (sfVector2f) {10, 10}) != BGS_OK) {
        return (RET_ERR_MALLOC);
    }
    list_add_to_end(scene->updates, obj);
    list_add_to_end(scene->displayables, obj);
    return (RET_OK);
}

int create_texts(scene_t *scene)
{
    int ret_code = 0;

    ret_code = create_texts_life(scene);
    if (ret_code != RET_OK) {
        return (RET_ERR_MALLOC);
    }
    ret_code = create_texts_score(scene);
    if (ret_code != RET_OK) {
        return (RET_ERR_MALLOC);
    }
    return (RET_OK);
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** utility function for an ennemy
*/

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "defender_game_data.h"
#include "list.h"
#include "my_conversions.h"
#include "my_strings.h"
#include "my_bgs.h"
#include "defender_ennemy.h"
#include "my_dico.h"

void update_score_text(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win,
        float dtime)
{
    static float time_free = 0;

    time_free += dtime;
    if (time_free > 5) {
        list_add_to_start(scene->to_remove, obj);
        time_free -= 5;
    } else {
        sfText_scale(obj->drawable.text, (sfVector2f) {1.01, 1.01});
        sfText_move(obj->drawable.text, (sfVector2f) {0, -0.5});
    }
}

void add_score_game(scene_t *scene, game_data_t *game, ennemy_t *enn,
        object_t *enn_obj)
{
    object_t *object = NULL;
    sfVector2f pos = {0};
    char buff[256] = {"+"};
    char *tmp = NULL;

    game->com += enn->com;
    game->xp += enn->xp;
    tmp = my_itoa(enn->xp);
    if (tmp == NULL) {
        return;
    }
    my_strcat(buff, tmp);
    free(tmp);
    pos = sfSprite_getPosition(enn_obj->drawable.sprite);
    object = create_object(update_score_text, NULL, scene);
    if (object == NULL) {
        return;
    }
    object_set_text(object, "./assets/font/menlo.ttf", buff, pos);
    list_add_to_end(scene->displayables, object);
    list_add_to_end(scene->updates, object);
}

void check_ennemy_alive(object_t *obj, float dtime, window_t *win,
        scene_t *scene)
{
    ennemy_t *enn = NULL;
    game_data_t *game = NULL;

    if (obj == NULL || win == NULL || scene == NULL) {
        return;
    }
    enn = dico_t_get_value(obj->components, OBJ_COMP_ENNSTRUCT);
    game = dico_t_get_value(win->components, GAME_DATA);
    if (enn == NULL || game == NULL) {
        return;
    }
    enn->time_last += dtime;
    enn->time_last_update += dtime;
    if (obj->is_visible == true && enn->life <= 0) {
        obj->is_visible = false;
        add_score_game(scene, game, enn, obj);
    }
}

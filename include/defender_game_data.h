/*
** EPITECH PROJECT, 2022
** defender
** File description:
** game data header
*/

#ifndef GAME_DATA_H_
    #define GAME_DATA_H_

    #include "my_dico.h"
    #include "defender.h"

static const char GAME_DATA[] = "game data";
static const char PAUSE_OBJ[] = "pause obj";
static const char SHOP_OBJ[] = "shop obj";

static const char GAME_DATA_PATH[] = "./assets/data/game/data.json";

typedef struct game_data_s {
    int level_progression;
    int com;
    int xp;
    dico_t *skill_three;
} game_data_t;

int init_game_data(window_t *win);

void click_shop_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

int init_side_menu(window_t *win, scene_t *scene);

void click_pause_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

#endif /* !GAME_DATA_H_ */

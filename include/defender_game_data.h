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

static const char TOWER_DATA[] = "tower data";
static const char SIZE[] = "size";
static const char GAME_DATA[] = "game data";
static const char PAUSE_OBJ[] = "pause obj";
static const char SHOP_OBJ[] = "shop obj";
static const char ENNEMY_ID[] = "ennemy id";

static const char GAME_DATA_PATH[] = "./assets/data/game/data.json";

static const char SCOPE_PATH[] = "./assets/image/tower/scope.png";
static const int SCOPE_RGBA[] = {255, 255, 255, 100};

typedef struct game_data_s {
    int level_progression;
    int com;
    int xp;
    dico_t *skill_three;
} game_data_t;

typedef struct tower_data_s {
    list_ptr_t *scope;
    int damage;
    int cadence;
    bool fly;
} tower_data_t;

object_t *place_support(any_t *size, scene_t *scene, sfVector2f pos);

int init_game_data(window_t *win);

void display_scope(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void hide_scope(object_t *obj, scene_t *scene, window_t *win, set_event_t *evt);

void click_shop_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

int init_side_menu(window_t *win, scene_t *scene);

void pause_back_update(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt);

void click_pause_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_resume_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void update_tower(object_t *obj, scene_t *scene, window_t *win, float time);

int create_tower(scene_t *scene, dico_t *tower, sfVector2f pos);

int set_scope(dico_t *tower_dico, dico_t *components[2], object_t *support,
    scene_t *scene);

#endif /* !GAME_DATA_H_ */

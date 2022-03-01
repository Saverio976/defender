/*
** EPITECH PROJECT, 2021
** defender
** File description:
** project header
*/

#ifndef defender_H_
    #define defender_H_

    #include "my_bgs.h"
    #include "my_bgs_components.h"

    #define RET_OK 0
    #define RET_INVALID_INPUT 1
    #define RET_ERR_MALLOC 2

    #define LEVEL_DATA_lEN 31
    #define EXTENSION_LEN 5

static const char MAIN_MENU[] = "./assets/data/game/menu/main.json";
static const char LEVEL_MENU[] = "./assets/data/game/menu/level.json";
static const char LEVEL_DATA[] = "./assets/data/game/level/level_";
static const char EXTENSION[] = ".json";

window_t *init_defender(int ac, char **av);

int init_main_menu(window_t *win);

int create_button(scene_t *scene, char const path[]);

int launch_game(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

void on_hover_menu_but(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

void off_hover_menu_but(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

void click_play_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

void click_settings_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

void click_quit_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

int init_level_menu(window_t *win);

void click_level_button(object_t *obj, dico_t *dico, window_t *win,
    set_event_t *evt);

#endif

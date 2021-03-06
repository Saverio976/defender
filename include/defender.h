/*
** EPITECH PROJECT, 2021
** defender
** File description:
** project header
*/

#ifndef defender_H_
    #define defender_H_

    #include "my_bgs.h"
    #include "my_json.h"
    #include "my_bgs_components.h"
    #include <SFML/Audio/Types.h>

    #define RET_OK 0
    #define RET_INVALID_INPUT 1
    #define RET_ERR_MALLOC 2

    #define LEVEL_DATA_lEN 31
    #define EXTENSION_LEN 5

    #define SQUARE_START_POS 20
    #define SQUARE_POS_INCREMENTATION 40

static const char END_MENU[] = "./assets/data/game/menu/end.json";
static const char SETTING_MENU[] = "./assets/data/game/menu/setting.json";
static const char PAUSE_MENU[] = "./assets/data/game/menu/pause.json";
static const char SHOP_MENU[] = "./assets/data/game/menu/shop.json";
static const char SIDE_MENU[] = "./assets/data/game/menu/side.json";
static const char MAIN_MENU[] = "./assets/data/game/menu/main.json";
static const char LEVEL_MENU[] = "./assets/data/game/menu/level.json";
static const char LEVEL_DATA[] = "./assets/data/game/level/level_";
static const char EXTENSION[] = ".json";

struct load_s {
    char *ennemy_file;
    float time;
    int spawn;
};
typedef struct load_s load_t;

struct level_data_s {
    int tower_nico_life;
};
typedef struct level_data_s level_data_t;

struct sound_buffer_s {
    sfSound *sound;
    sfSoundBuffer *buffer;
};
typedef struct sound_buffer_s sound_buffer_t;

window_t *init_defender(int ac, char **av);

int create_map(scene_t *scene, char const *path, any_t *squares_path);

int init_main_menu(window_t *win);

int create_button(scene_t *scene, char const path[]);

int launch_game(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void on_hover_menu_but(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

list_ptr_t *create_load_list(any_t *wave, any_t *ennemy_file);

void off_hover_menu_but(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

int create_texts(scene_t *scene);

void click_play_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_settings_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void show_next_how2(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_quit_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_show_how2(object_t *obj, scene_t *scene, window_t *win,
        set_event_t *evt);

int init_level_menu(window_t *win);

void click_level_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void destroy_load_list(void *data);

void update_score_total_text(object_t *obj, scene_t *scene, window_t *win,
        float dtime);

void update_com_total_text(object_t *obj, scene_t *scene, window_t *win,
        float dtime);

void update_wave_launcher(object_t *obj, scene_t *scene,
    window_t *win, float dtime);

void check_set_color(object_t *object, dico_t *dico);

int init_how2play(window_t *win);

int create_texts_score(scene_t *scene);

int init_background_menu(scene_t *scene);

int init_events_scoe(object_t *obj);

#endif

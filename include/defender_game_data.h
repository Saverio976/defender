/*
** EPITECH PROJECT, 2022
** defender
** File description:
** game data header
*/

#ifndef GAME_DATA_H_
    #define GAME_DATA_H_

    #include "my_bgs.h"
    #include "my_dico.h"
    #include "defender.h"
    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics/Rect.h>

static const char TOWER_DATA[] = "tower data";
static const char SIZE[] = "size";
static const char GAME_DATA[] = "game data";
static const char PAUSE_OBJ[] = "pause obj";
static const char TOWER_LIST[] = "tower list";
static const char SHOP_OBJ[] = "shop obj";
static const char ENNEMY_ID[] = "ennemy id";

static const char END_GAME[] = "end game";
static const char POISON_LIST[] = "poison list";

static const char AUDIO_PATH[] = "./assets/sound/audio.ogg";

static const char MUSIC_OBJ[] = "music obj";
static const char SOUND_OBJ[] = "sound obj";

static const char GAME_DATA_PATH[] = "./assets/data/game/data.json";

static const char SCOPE_PATH[] = "./assets/image/tower/scope.png";
static const int SCOPE_RGBA[] = {255, 255, 255, 100};
static const float TOWER_ROTATION = 0.5;

typedef struct error_message_data_s {
    int frame_counter;
} error_message_data_t;

typedef struct game_data_s {
    int level_progression;
    int com;
    int xp;
    bool music;
    bool sound_effect;
    dico_t *skill_three;
    char *font;
} game_data_t;

typedef struct tower_data_s {
    sfCircleShape *scope;
    float scope_rad;
    bool scope_display;
    int damage;
    float cadence;
    int fly;
    float dtime;
    char *sprite_bullet;
    sfIntRect sprite_int_rect;
    sfSoundBuffer *sound_buffer;
    sfSound *sound;
} tower_data_t;

typedef struct poison_s {
    sfCircleShape *scope;
    float scope_rad;
    float timer;
} poison_t;

object_t *place_support(any_t *size, scene_t *scene, sfVector2f pos);

int set_aud(scene_t *scene, window_t *win);

void click_buy_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void update_drag(object_t *obj, __attribute__((unused)) scene_t *scene,
    window_t *win, __attribute__((unused)) float time);

object_t *fill_data_bullet(object_t *obj, dico_t *dico,
        tower_data_t *tower_data);

void check_open_elem(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt);

void place_tower(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void display_poison(object_t *obj, __attribute__((unused)) dico_t
    *scene_comp, __attribute__((unused)) dico_t *win_com, sfRenderWindow *win);

void update_poison(object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win, float time);

void click_escape_button(__attribute__((unused)) object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt);

int init_game_data(window_t *win);

bool check_drag_pos(window_t *win, int size);

int destroy_elem(float *pos, int *clr, float *scd_pos, int *scdclr);

int init_setting_menu(window_t *win);

void end_game(scene_t *scene, bool win);

void shot_ennemy(object_t *ennemy_obj, object_t *tower,
        tower_data_t *tower_data, scene_t *scene);

bool check_money(game_data_t *game_data, dico_t *tower, sfVector2f pos,
    scene_t *scene);

void buy_poison(__attribute__((unused)) object_t *obj, scene_t *scene,
    __attribute__((unused)) window_t *win,
    __attribute__((unused)) set_event_t *evt);

void display_scope(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void hide_scope(object_t *obj, scene_t *scene, window_t *win, set_event_t *evt);

bool create_txt_place_err(object_t *support, scene_t *scene, window_t *win);

void click_shop_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

int init_side_menu(window_t *win, scene_t *scene);

void click_quit_level_button(object_t *obj, scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt);

void destroy_poison_data(void *data);

void click_sound_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_music_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_back_button(__attribute__((unused)) object_t *obj,
    __attribute__((unused)) scene_t *scene, window_t *win,
    __attribute__((unused)) set_event_t *evt);

void click_pause_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void click_resume_button(object_t *obj, scene_t *scene, window_t *win,
    set_event_t *evt);

void update_tower(object_t *obj, scene_t *scene, window_t *win, float time);

bool check_circle_col(object_t *ennemy, sfVector2f circle, float rad);

int create_tower(scene_t *scene, dico_t *tower, sfVector2f pos);

int set_scope(dico_t *components[2], object_t *support);

void free_list_void(void *data);

void update_shop_error_message(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win, float dtime);

void set_end_game(scene_t *scene, window_t *win, bool state);

void add_to_poison_list(scene_t *scene, object_t *poison);

void create_drag(scene_t *scene, window_t *win, dico_t *tower,
    char *tower_path);

#endif /* !GAME_DATA_H_ */

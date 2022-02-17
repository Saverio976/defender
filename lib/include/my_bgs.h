/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** bgs
*/

#ifndef BGS_H_
    #define BGS_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdbool.h>
    #include "list.h"
    #include "my_dico.h"

    #define BGS_OK 0
    #define BGS_ERR_PATH 1
    #define BGS_ERR_MALLOC 2
    #define BGS_ERR_INPUT 3

typedef struct time_clock_s time_clock_t;
typedef struct object_s object_t;
typedef struct window_s window_t;
typedef struct scene_s scene_t;

enum object_type {
    SPRITE,
    TEXT,
    AUDIO,
    CUSTOM,
    UNSET
};

struct object_s {
    enum object_type type;
    union bigdata {
        sfTexture *texture;
        sfFont *font;
    } bigdata;
    union drawable {
        sfSprite *sprite;
        sfText *text;
        sfMusic *music;
    } drawable;
    dico_t *components;
    void (*update)(object_t *, void *scene_data, window_t *win, float);
    void (*display)(object_t *, void *scene_data, void *win_data,
        sfRenderWindow *win);
};

struct time_clock_s {
    float seconds;
    float refresh_time;
    sfClock *clock;
    sfTime time;
};

struct scene_s {
    sfColor bg_color;
    list_ptr_t *updates;
    list_ptr_t *objects;
    list_ptr_t *displayables;
    void *data;
    void (*destroy)(void *);
};

struct window_s {
    sfRenderWindow *win;
    int scene_index;
    list_ptr_t *scenes;
    void *data;
    void (*destroy)(void *);
};

int event_handling(sfRenderWindow *win);
object_t *get_obj_from_list(list_t *list);
scene_t *get_scene_i(list_ptr_t *list, int i);
int scene_add_object(scene_t *scene, object_t *object);
int window_add_scene(window_t *win, scene_t *scene);
object_t *get_obj_from_list(list_t *list);
scene_t *create_scene(void *(*create)(void), void (*destroy)(void *),
    window_t *win, sfColor bg_color);
int object_set_audio(object_t *object, char const *path, bool play_now,
    bool is_loop);
int loop(window_t *win);
void remove_window(window_t *win);
window_t *create_window(sfVideoMode mode, const char *title, void *(*create)(void),
    void (*destroy)(void *));
object_t *create_object(
    void (*update)(object_t *, void *, window_t *win, float),
    void (*display)(object_t *, void *, void *, sfRenderWindow *),
    scene_t *scene);
int object_set_custom(object_t *object, void *(*create)(void),
    void (*destroy)(void *), char *key);
void display_sprite(object_t *object, void *scene_data, void *win_data,
    sfRenderWindow *win);
void display_text(object_t *object, void *scene_data, void *win_data,
    sfRenderWindow *win);
int object_set_sprite(object_t *object, char const *path, scene_t *scene);
int object_set_text(object_t *object, char const *path, char const *text,
    scene_t *scene);

#endif /* !BGS_H_ */

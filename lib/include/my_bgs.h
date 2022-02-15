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

typedef struct time_clock_s time_clock_t;
typedef struct object_s object_t;
typedef struct window_s window_t;
typedef struct scene_s scene_t;

enum object_type {
    SPRITE,
    TEXT,
    AUDIO,
    CUSTOM
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
        void *custom;
    } drawable;
    void *data;
    void (*destroy)(void *);
    void (*update)(object_t *, void *scene_data, void *win_data, float);
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
scene_t *get_scene_i(list_ptr_t *list, int i);
object_t *get_obj_from_list(list_t *list);
int object_set_sprite(object_t *object, char const *path);
int object_set_text(object_t *object, char const *path, char const *text);
int object_set_cutsom(object_t *object, void *(*create)(void));
scene_t *create_scene(void *(*create)(void), void (*destroy)(void *));
int object_set_audio(object_t *object, char const *path, bool play_now,
    bool is_loop);
int loop(window_t *win);
void remove_window(window_t *win);
window_t *create_window(sfVideoMode mode, const char *title, void *(*create)(void),
    void (*destroy)(void *));
object_t *create_object(void *(*create)(void), void (*destroy)(void *),
    void (*update)(object_t *, void *scene_data, void *win_data, float),
    void (*display)(object_t *, void *scene_data, void *win_data,
    sfRenderWindow *win));

#endif /* !BGS_H_ */

/*
** EPITECH PROJECT, 2022
** LIBGRAS
** File description:
** libgras header
*/

#ifndef MY_LIBGRAS_H_
    #define MY_LIBGRAS_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

typedef struct window_entity_s window_entity_t;
typedef struct scene_entity_s scene_entity_t;
typedef struct object_entity_s object_entity_t;
typedef struct component_entity_s component_entity_t;

/*
*******************************************************************************
** component
*/

enum component_entity_type {
    GRAVITY,
    MOOVE,
    ANNIM,
    CUSTOM
};

struct component_gravity_s {
    float gravity_force_x;
    float gravity_force_y;
    float vector_x;
    float vector_y;
};
typedef struct component_gravity_s component_gravity_t;

struct component_moove_s {
    sfVector2f vector;
};
typedef struct component_moove_s component_moove_t;

    #define NB_RECT_MAX 20

struct component_annimated_sprite_s {
    int nb_rect;
    sfIntRect rect[NB_RECT_MAX];
    sfClock *clock;
    float annim_per_seconds;
};
typedef struct component_annimated_sprite_s component_annimated_sprite_t;

struct component_custom_s {
    int custom_type_int;
    void *data;
};
typedef struct component_custom_s component_custom_s;

struct component_entity_s {
    enum component_entity_type type;
    union component_entity_u {
        component_gravity_t gravity;
        component_moove_t moove;
        component_annimated_sprite_t annim;
        component_custom_s custom;
    } component;
};

/*
*******************************************************************************
** object entity
*/

enum object_entity_type {
    SPRITE,
    TEXT,
    SOUND,
    MUSIC
};

    #define NB_COMPONENT_MAX 5

struct object_entity_s {
    enum object_entity_type type;
    int custom_type_int;
    union base_union {
        sfTexture *texture;
        sfFont *font;
        sfSoundBuffer *sound_buffer;
    } base;
    union obj_union {
        sfSprite *sprite;
        sfText *text;
        sfSound *sound;
        sfMusic *music;
    } obj;
    int nb_component;
    component_entity_t components[NB_COMPONENT_MAX];
    float seconds;
    object_entity_t *next;
};

/*
*******************************************************************************
** scene entity
*/

struct scene_entity_s {
    int zindex;
    void *(*create)(scene_entity_t *);
    int (*update)(scene_entity_t *); //TODO: take window entity
    void (*destroy)(void *);
    float seconds;
    void *data;
    object_entity_t *list_object;
    scene_entity_t *next;
};

/*
*******************************************************************************
** window entity
*/

struct window_entity_s {
    int current_zindex;
    scene_entity_t *list_scene;
    sfRenderWindow *win;
    sfEvent *event;
    sfClock *clock;
    void *custom_data;
    void *(*create)(window_entity_t *);
    void (*destroy)(void *);
};

#endif

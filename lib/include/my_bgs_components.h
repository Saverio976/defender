/*
** EPITECH PROJECT, 2022
** Defender
** File description:
** my bgs components
*/

#ifndef BGS_COMPONENTS_
    #define BGS_COMPONENTS_

    #include "my_bgs.h"

static const char ON_HOVER_KEY[] = "__on_hover";
static const char ON_RIGHT_KEY[] = "__on_right_click";
static const char ON_LEFT_KEY[] = "__on_left_click";

typedef struct sprite_anim_s sprite_anim_t;
typedef struct sprite_move_s sprite_move_t;
typedef struct sprite_health_s sprite_health_t;
typedef struct sprite_solid_s sprite_solid_t;
typedef struct sprite_chrono_s sprite_chrono_t;
typedef struct on_left_click_s on_left_click_t;
typedef struct on_right_click_s on_right_click_t;
typedef struct on_hover_s on_hover_t;

struct sprite_anim_s {
    sfIntRect rect;
};

struct sprite_move_s {
    sfVector2f vect;
};

struct sprite_health_s {
    float life;
    float max_life;
};

struct sprite_solid_s {
};

struct sprite_chrono_s {
    float seconds;
    float refresh_rate;
};

struct on_hover_s {
    void (*hover)(object_t *, void *, window_t *win);
};

struct on_right_click_s {
    void (*right_click)(object_t *, void *, window_t *win);
};

struct on_left_click_s {
    void (*left_click)(object_t *, void *, window_t *win);
};

int object_add_components(object_t *object, void *data, const char key[],
    void (*destroy)(void *));
int object_add_hover_event(object_t *object, void (*hover)(object_t *, void *,
    window_t *win));
int object_add_right_click_event(object_t *object,
    void (*right_click)(object_t *, void *, window_t *win));
int object_add_left_click_event(object_t *object, void (*left_click)(object_t *,
    void *, window_t *win));
int object_add_chrono(object_t *object, float seconds,
    float refresh_rate);
int object_add_sprite_text_solid(object_t *object);
int object_add_sprite_health(object_t *object, float life, float max_life);
int object_add_sprite_move(object_t *object, sfVector2f vect);
int object_add_sprite_anim(object_t *object, sfIntRect rect);
void object_update(object_t *object, void *scene_data, window_t *win);

#endif /* !BGS_COMPONENTS_ */

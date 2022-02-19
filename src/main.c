/*
** EPITECH PROJECT, 2021
** defender
** File description:
** the main entry point for the project
*/

#include <stdbool.h>
#include "my_puts.h"
#include "my_bgs.h"
#include "my_bgs_components.h"

void set(object_t *object,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win)
{
    set_display(object);
}

void unset(object_t *object,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win)
{
    unset_display(object);
}
void click_die(object_t *this,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win)
{
    sprite_health_t *health = dico_t_get_value(this->components, COMP_HEALTH);

    if (health == NULL) {
        return;
    }
    health->life -= 1;
    my_putstr("click_die\n");
}

void collision(object_t *this, object_t *other,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win)
{
    object_t *background = dico_t_get_value(scene_components, "BACK");

    if (background->is_visible == true) {
        unset_display(background);
    } else {
        set_display(background);
    }
}

void move_left(object_t *object,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win)
{
    if (object->type == SPRITE) {
        sfSprite_move(object->drawable.sprite, (sfVector2f) {-50, 0});
    } else if (object->type == TEXT) {
        sfText_move(object->drawable.text, (sfVector2f) {-50, 0});
    }
}

void move_right(object_t *object,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win)
{
     if (object->type == SPRITE) {
        sfSprite_move(object->drawable.sprite, (sfVector2f) {50, 0});
    } else if (object->type == TEXT) {
        sfText_move(object->drawable.text, (sfVector2f) {50, 0});
    }
}

int main(void)
{
    window_t *win = create_window(((sfVideoMode) {1920, 1080, 32}), "test", sfResize | sfClose);
    scene_t *scene = create_scene(win, sfBlack);
    object_t *music = create_object(NULL, NULL, scene);
    object_t *background = create_object(NULL, NULL, scene);
    object_t *text = create_object(NULL, NULL, scene);
    object_t *sprite = create_object(NULL, NULL, scene);
    set_event_t *event = create_event(&click_die, NULL, true, sprite);

    if (sprite == NULL || event == NULL) {
        return 84;
    }
    window_set_icon(win, "assets/icon/xp_icon.jpg");
    event_add_node(event, (node_params_t) {sfMouseRight, sfKeySpace, MOUSE});
    object_set_audio(music, "assets/music/rickroll.ogg", true, true);
    object_set_sprite(sprite, "assets/map/castle_with_nico.png");
    object_set_sprite(background, "assets/map/back.png");
    object_add_sprite_health(sprite, 1, 1, &unset);
    sfSprite_setPosition(sprite->drawable.sprite, (sfVector2f) {200, 0});
    object_set_text(text, "assets/font/menlo.ttf", "OUIII");
    loop(win);
    remove_window(win);
    return 0;
}

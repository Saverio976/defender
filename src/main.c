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

void collision(object_t *this, object_t *other, dico_t *scene_components,
    window_t *win) {
    printf("collision");
    if (this->is_visible == true) {
        unset_display(this);
    } else {
        set_display(this);
    }
    if (other->is_visible == true) {
        unset_display(other);
    } else {
        set_display(other);
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
    window_t *win = create_window(((sfVideoMode) {1920, 1080, 32}), "test");
    scene_t *scene = create_scene(win, sfBlack);
    object_t *music = create_object(NULL, NULL, scene);
    object_t *background = create_object(NULL, NULL, scene);
    object_t *text = create_object(NULL, NULL, scene);
    object_t *sprite = create_object(NULL, NULL, scene);
    set_event_t evt = {0};

    if (sprite == NULL) {
        return 84;
    }
    //faire une ptn de fct pour preset facilement set_envent_t parcque si on doit faire tout ca a chaque fois ca va pas le faire
    evt.hover = false;
    evt.off = &set;
    evt.on = &unset;
    evt.list_event = list_create();
    event_node_t *node = malloc(sizeof(event_node_t));
    node->event_type = KEY;
    node->event_code.key = sfKeyA;
    list_add_to_end(evt.list_event, node);
    if (evt.list_event == NULL) {
        return (84);
    }
    evt.prev_call = false;
    object_set_audio(music, "assets/music/rickroll.ogg", true, true);
    object_set_sprite(sprite, "assets/map/castle_with_nico.png");
    object_set_sprite(background, "assets/map/back.png");
    //object_set_event(sprite, &evt);
    sfSprite_setPosition(sprite->drawable.sprite, (sfVector2f) {200, 0});
    object_set_text(text, "assets/font/menlo.ttf", "OUIII");
    object_add_right_click_event(sprite, &move_right);
    object_add_left_click_event(sprite, &move_left);
    object_add_right_click_event(text, &move_right);
    object_add_left_click_event(text, &move_left);
    object_add_collision(sprite, scene, &collision);
    object_add_collision(text, scene, NULL);
    loop(win);
    remove_window(win);
    return 0;
}

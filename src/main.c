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
        __attribute__((unused)) window_t *win, set_event_t *event)
{
    if (object->type == SPRITE) {
        object->bigdata.sprite_bigdata.pos.x -= 15;
    } else if (object->type == TEXT) {
        object->bigdata.text_bigdata.pos.x -= 15;
    }
}

void move_right(object_t *object,
        __attribute__((unused)) dico_t *scene_components,
        __attribute__((unused)) window_t *win, set_event_t *event)
{
     if (object->type == SPRITE) {
        object->bigdata.sprite_bigdata.pos.x += 15;
    } else if (object->type == TEXT) {
        object->bigdata.text_bigdata.pos.x += 15;
    }
}

int main(void)
{
    window_t *win = create_window(((sfVideoMode) {1920, 1080, 32}), "test", sfResize | sfClose);
    scene_t *scene = create_scene(win, sfBlack);
    object_t *music = create_object(NULL, NULL, scene);
    object_t *background = create_object(NULL, NULL, scene);
    scene_add_components(scene, background, "BACK", NULL);
    object_t *sprite = create_object(NULL, NULL, scene);
    object_t *other = create_object(NULL, NULL, scene);
    set_event_t *event = create_event(&move_right, false, sprite, NULL);

    event_add_node(event, (node_params_t) {sfMouseRight, sfKeyZ, KEY});
    event = create_event(&move_left, false, sprite, NULL);
    event_add_node(event, (node_params_t) {sfMouseRight, sfKeyA, KEY});
    event = create_event(&move_right, false, other, NULL);
    event_add_node(event, (node_params_t) {sfMouseRight, sfKeyO, KEY});
    event = create_event(&move_left, NULL, other, NULL);
    event_add_node(event, (node_params_t) {sfMouseRight, sfKeyI, KEY});
    if (sprite == NULL) {
        return 84;
    }
    window_set_icon(win, "assets/icon/xp_icon.jpg");
    object_set_audio(music, "assets/music/rickroll.ogg", true, true);
    object_set_sprite(sprite, "assets/map/castle_with_nico.png", (sfIntRect) {-1, -1, -1, -1}, (sfVector2f) {200, 0});
    object_set_sprite(background, "assets/map/back.png", (sfIntRect) {-1, -1, -1, -1}, (sfVector2f) {-1, -1});
    object_set_sprite(other, "assets/ennemy/tank.png", (sfIntRect) {0, 0, 105, 105}, (sfVector2f) {400, 100});
    my_putstr("before\n");
    object_add_collision(sprite, scene, &collision, true);
    my_putstr("while\n");
    object_add_collision(other, scene, NULL, true);
    my_putstr("after\n");
    loop(win);
    remove_window(win);
    return 0;
}

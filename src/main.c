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

void update(object_t *object, dico_t *scene_components, window_t *win, float seconds)
{
    //my_printf("oe\n");
}

void right_click(object_t *object, dico_t *scene_components, window_t *win)
{
    sfVector2f offset = {20, 0};

    if (object->type == SPRITE) {
        sfSprite_move(object->drawable.sprite, offset);
    } else if (object->type == TEXT) {
        sfText_move(object->drawable.text, offset);
    } else {
        return;
    }
}

void left_click(object_t *object, dico_t *scene_components, window_t *win)
{
    sfVector2f offset = {0, 20};

    if (object->type == SPRITE) {
        sfSprite_move(object->drawable.sprite, offset);
    } else if (object->type == TEXT) {
        sfText_move(object->drawable.text, offset);
    } else {
        return;
    }
}

int main(int ac, char **av)
{
    window_t *win = create_window(((sfVideoMode) {1920, 1080, 32}), "test");
    scene_t *scene = create_scene(NULL, NULL, win, sfBlack);
    object_t *music = create_object(NULL, NULL, scene);
    object_t *text = create_object(NULL, NULL, scene);
    object_t *sprite = create_object(&update, NULL, scene);

    if (sprite == NULL) {
        return 84;
    }
    object_set_audio(music, "assets/music/rickroll.ogg", true, true);
    object_set_sprite(sprite, "assets/map/castle_with_nico.png", scene);
    object_set_text(text, "assets/font/menlo.ttf", "OUIII", scene);
    object_add_right_click_event(sprite, &right_click);
    object_add_left_click_event(sprite, &left_click);
    loop(win);
    remove_window(win);
    return 0;
}

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

void set(object_t *object, dico_t *scene_components, window_t *win)
{
    set_display(object);
}

void unset(object_t *object, dico_t *scene_components, window_t *win)
{
    unset_display(object);
}

int main(int ac, char **av)
{
    window_t *win = create_window(((sfVideoMode) {1920, 1080, 32}), "test");
    scene_t *scene = create_scene(NULL, NULL, win, sfBlack);
    object_t *music = create_object(NULL, NULL, scene);
    object_t *text = create_object(NULL, NULL, scene);
    object_t *sprite = create_object(NULL, NULL, scene);

    if (sprite == NULL) {
        return 84;
    }
    object_set_audio(music, "assets/music/rickroll.ogg", true, true);
    object_set_sprite(sprite, "assets/map/castle_with_nico.png");
    sfSprite_setPosition(sprite->drawable.sprite, (sfVector2f) {200, 200});
    object_set_text(text, "assets/font/menlo.ttf", "OUIII");
    object_add_right_click_event(sprite, &set);
    object_add_left_click_event(sprite, &unset);
    object_add_right_click_event(text, &set);
    object_add_left_click_event(text, &unset);
    loop(win);
    remove_window(win);
    return 0;
}

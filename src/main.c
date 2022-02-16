/*
** EPITECH PROJECT, 2021
** defender
** File description:
** the main entry point for the project
*/

#include <stdbool.h>
#include "my_puts.h"
#include "my_bgs.h"

void update(object_t *object, void *scene_data, window_t *win, float seconds)
{
    //my_printf("oe\n");
}

int main(int ac, char **av)
{
    window_t *win = create_window(((sfVideoMode) {1920, 1080, 32}), "test",
        NULL, NULL);
    scene_t *scene = create_scene(NULL, NULL, win);
    object_t *music = create_object(NULL, NULL, scene);
    object_t *text = create_object(NULL, NULL, scene);
    object_t *sprite = create_object(&update, NULL, scene);

    if (sprite == NULL) {
        return 84;
    }
    object_set_audio(music, "assets/music/rickroll.ogg", true, true);
    object_set_sprite(sprite, "assets/map/castle_with_nico.png", scene);
    object_set_text(text, "assets/font/menlo.ttf", "OUIII", scene);
    loop(win);
    remove_window(win);
    return 0;
}

/*
** EPITECH PROJECT, 2021
** defender
** File description:
** the main entry point for the project
*/

#include "my_puts.h"
#include "my_bgs.h"

void display(object_t *object, __attribute((unused)) void *scene_data,
        __attribute((unused)) void *win_data, sfRenderWindow *win)
{
    sfRenderWindow_drawSprite(win, object->drawable.sprite, NULL);
}

int main(int ac, char **av)
{
    window_t *win = NULL;
    sfVideoMode mode = {1920, 1080, 32};
    scene_t *scene = NULL;
    object_t *object = NULL;
    int ret_code = 0;

    for (int i = 0; i < ac; i++)
        my_printf("%s\n", av[i]);
    win = create_window(mode, "DEFENDER", NULL, NULL);
    if (win == NULL) {
        return 84;
    }
    scene = create_scene(NULL, NULL);
    if (window_add_scene(win, scene) == 84) {
        return 84;
    }
    object = create_object(NULL, NULL, NULL, &display);
    if (object == NULL) {
        return (84);
    }
    object_set_sprite(object, "./assets/map/castle.png");
    scene_add_object(scene, object);
    win->scene_index = 0;
    ret_code = loop(win);
    remove_window(win);
    return (ret_code);
}

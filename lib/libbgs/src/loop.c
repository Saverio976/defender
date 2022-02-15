/*
** EPITECH PROJECT, 2022
** bgs
** File description:
** loop
*/

#include "my_bgs.h"

void window_display(scene_t *scene, window_t *win)
{
    object_t *obj = NULL;
    list_t *elem = scene->displayables->start;

    for (int i = 0; i < scene->updates->len; i++) {
        obj = ((object_t *) elem->var);
        obj->display(obj, scene->data, win->data, win->win);
        elem = elem->next;
    }
    sfRenderWindow_display(win->win);
}

void window_update(scene_t *scene, window_t *win, float seconds)
{
    object_t *obj = NULL;
    list_t *elem = scene->updates->start;

    for (int i = 0; i < scene->updates->len; i++) {
        obj = ((object_t *) elem->var);
        obj->update(obj, scene->data, win->data, seconds);
        elem = elem->next;
    }
}

time_t *init_clock(void)
{
    time_t *timer = malloc(sizeof(time_t));

    if (timer == NULL) {
        return NULL;
    }
    timer->clock = sfClock_create();
    return timer;
}

int scene_handling(window_t *win, scene_t *scene, time_t *timer)
{
    static int last_index = -1;

    if (last_index != win->scene_index) {
        scene = get_scene_i(win->scenes, win->scene_index);
        last_index = win->scene_index;
    }
    if (scene == NULL) {
        return 84;
    }
    timer->time = sfClock_restart(timer->clock);
    timer->seconds = sfTime_asSeconds(timer->time);
    window_update(scene, win, timer->seconds);
    window_display(scene, win);
    return 0;
}

int loop(window_t *win)
{
    scene_t *scene = NULL;
    time_t *timer = init_clock();

    if (timer == NULL || win->scenes->len == 0) {
        return 0;
    }
    while (sfRenderWindow_isOpen(win->win)) {
        if (scene_handling(win, scene, timer) == 84) {
            return 84;
        }
    }
    sfClock_destroy(timer->clock);
    free(timer);
    return 0;
}

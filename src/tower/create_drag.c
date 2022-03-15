/*
** EPITECH PROJECT, 2022
** defender
** File description:
** create drag
*/

#include <stdlib.h>
#include "my_wordarray.h"
#include "my_strings.h"
#include "defender_ennemy.h"
#include "defender_game_data.h"

float get_drag_pos(float pos, int size)
{
    int u = (pos / 40);
    u = u * 100;
    float a = (pos / 4) * 10;
    int w = ((int) a) - u;

    if (size % 2 == 0) {
        return (w > 50) ? (((int) pos / 40) + 1) * 40 : ((int) pos / 40) * 40;
    } else {
        return ((int) pos / 40) * 40 + 20;
    }
    return pos;
}

void update_drag_support(object_t *obj, scene_t *scene, window_t *win,
    float time)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(win->win);
    int size = (int) dico_t_get_value(obj->components, "tower size");
    char **map = dico_t_get_value(scene->components, SCENE_COMP_MAP);

    if (map == NULL) {
        return;
    }
    if (pos.y / 40 >= 0 && pos.y / 40 < my_wordarray_len(map)) {
        obj->bigdata.sprite_bigdata.pos.y = get_drag_pos(pos.y, size);
    }
    if (pos.x / 40 >= 0 && ((pos.y / 40 < my_wordarray_len(map) && pos.y > 0) &&
        pos.x / 40 < my_strlen(map[pos.y / 40]))) {
        obj->bigdata.sprite_bigdata.pos.x = get_drag_pos(pos.x, size);
    }
}

void update_drag(object_t *obj, scene_t *scene, window_t *win, float time)
{
    sfVector2i posi = sfMouse_getPositionRenderWindow(win->win);

    obj->bigdata.sprite_bigdata.pos = (sfVector2f) {(float) posi.x,
        (float) posi.y};
}

int create_support_drag(scene_t *scene, object_t *drag, int size,
    char *path[2])
{
    object_t *drag_support = create_object(update_drag_support, NULL, scene);

    if (drag_support == NULL || object_set_sprite(drag_support, path[0],
            (sfIntRect) {-1, -1, -1, -1}, (sfVector2f) {-1, -1}) != BGS_OK) {
        return RET_ERR_MALLOC;
    }
    drag_support->components = dico_t_add_data(drag_support->components,
        "drag tower", drag, NULL);
    drag_support->components = dico_t_add_data(drag_support->components,
        "tower size", (void *) size, NULL);
    drag_support->components = dico_t_add_data(drag_support->components,
        "tower path", my_strdup(path[1]), free);
    list_add_to_end(scene->displayables, drag_support);
    list_add_to_start(scene->updates, drag_support);
    event_add_node(create_event(place_tower, false, drag_support, NULL),
        (node_params_t) {sfMouseLeft, sfKeyA, MOUSE});
    return RET_OK;
}

void create_drag(scene_t *scene, window_t *win, dico_t *tower, char *tower_path)
{
    object_t *drag = create_object(update_drag, NULL, scene);
    any_t *path = dico_t_get_any(tower, "path");
    sfVector2i posi = sfMouse_getPositionRenderWindow(win->win);
    sfVector2f pos = {(float) posi.x, (float) posi.y};
    any_t *size = dico_t_get_any(tower, "size");
    char *file_path[2] = {NULL, tower_path};

    if (drag == NULL || path == NULL || size == NULL || object_set_sprite(drag,
        path->value.str, (sfIntRect) {-1, -1, -1, -1}, pos) != BGS_OK) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (SIZE_ARR[i] == size->value.i) {
            file_path[0] = SUPPORT_PATH[i];
        }
    }
    create_support_drag(scene, drag, size->value.i, file_path);
    list_add_to_end(scene->displayables, drag);
    list_add_to_end(scene->updates, drag);
}

/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init the how to play scene
*/

#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "list.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "my_dico.h"
#include "defender.h"

void free_list_void(void *data);

static const char assets[9][50] = {
    "./assets/image/how2play/menu.png",
    "./assets/image/how2play/level.png",
    "./assets/image/how2play/game.png",
    "./assets/image/how2play/buy.png",
    "./assets/image/how2play/pause.png",
    "./assets/image/how2play/standart.png",
    "./assets/image/how2play/aerian.png",
    "./assets/image/how2play/riffle.png",
    "./assets/image/how2play/sniper.png"
};

static const sfIntRect all_rect = {-1, -1, -1, -1};

static const sfVector2f mid_pos = {1920.0 / 2, 1080.0 / 2};

void click_show_how2(__attribute__((unused)) object_t *obj,
        __attribute__((unused)) scene_t *scene,
        window_t *win, __attribute__((unused)) set_event_t *evt)
{
    win->scene_index = 3;
}

void show_next_how2(__attribute__((unused)) object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win,
        __attribute__((unused)) set_event_t *evt)
{
    static int current = 0;
    list_ptr_t *list = NULL;
    list_t *elem = NULL;
    object_t *obj_show = NULL;

    list = dico_t_get_value(scene->components, "CURSPRITE");
    if (list == NULL || list->len == 0) {
        return;
    }
    elem = list->start;
    current = (current + 1 > 8) ? 0 : current + 1;
    for (int i = 0; i < list->len; i++, elem = elem->next) {
        obj_show = elem->var;
        if (i == current) {
            obj_show->is_visible = true;
        } else {
            obj_show->is_visible = false;
        }
    }
}

static int init_sprites(scene_t *scene, list_ptr_t *list)
{
    object_t *obj = NULL;

    for (int i = 0; i < 9; i++) {
        obj = create_object(NULL, NULL, scene);
        if (obj == NULL) {
            return (0);
        }
        object_set_sprite(obj, assets[i], all_rect, mid_pos);
        if (i != 0) {
            obj->is_visible = false;
        }
        list_add_to_end(list, obj);
    }
    return (1);
}

int init_how2play(window_t *win)
{
    scene_t *scene = NULL;
    list_ptr_t *list = NULL;

    if (win == NULL) {
        return (0);
    }
    scene = create_scene(win, sfBlack);
    list = list_create();
    if (scene == NULL || list == NULL) {
        return (RET_ERR_MALLOC);
    }
    if (scene_add_components(scene, list, "CURSPRITE", free_list_void) != 0) {
        return (RET_ERR_MALLOC);
    }
    if (init_sprites(scene, list) != 1) {
        return (RET_ERR_MALLOC);
    }
    return (create_button(scene, "./assets/data/game/menu/how2play.json"));
}

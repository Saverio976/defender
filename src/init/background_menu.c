/*
** EPITECH PROJECT, 2022
** defender
** File description:
** init the how to play scene
*/

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "list.h"
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "my_dico.h"
#include "defender.h"

void free_list_void(void *data);

static const char assets[7][50] = {
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

static void update_next_custom(__attribute__((unused)) object_t *obj,
        scene_t *scene, __attribute__((unused)) window_t *win,
        float dtime)
{
    list_ptr_t *list = NULL;
    list_t *elem = NULL;
    object_t *obj_show = NULL;
    sfVector2f pos = {0};

    list = dico_t_get_value(scene->components, "CURSPRITE");
    if (list == NULL || list->len == 0) {
        return;
    }
    elem = list->start;
    dtime *= -200;
    for (int i = 0; i < list->len; i++, elem = elem->next) {
        obj_show = elem->var;
        obj_show->bigdata.sprite_bigdata.pos.x += dtime;
        pos = obj_show->bigdata.sprite_bigdata.pos;
        if (pos.x < -960) {
            obj_show->bigdata.sprite_bigdata.pos.x += (1920 * list->len);
        }
    }
}

static int init_sprites(scene_t *scene, list_ptr_t *list)
{
    object_t *obj = NULL;
    sfVector2f new_pos = mid_pos;

    for (int i = 0; i < 7; i++) {
        obj = create_object(NULL, NULL, scene);
        if (obj == NULL) {
            return (0);
        }
        object_set_sprite(obj, assets[i], all_rect, new_pos);
        new_pos.x += 1920.0;
        list_add_to_end(list, obj);
    }
    return (1);
}

static int init_how2play_custom(scene_t *scene)
{
    object_t *obj = NULL;

    obj = create_object(update_next_custom, NULL, scene);
    if (obj == NULL) {
        return (0);
    }
    object_set_custom(obj);
    return (1);
}

int init_background_menu(scene_t *scene)
{
    list_ptr_t *list = NULL;

    if (scene == NULL) {
        return (0);
    }
    list = list_create();
    if (scene == NULL || list == NULL) {
        return (RET_ERR_MALLOC);
    }
    if (scene_add_components(scene, list, "CURSPRITE", free_list_void) != 0) {
        return (RET_ERR_MALLOC);
    }
    if (init_sprites(scene, list) != 1 || init_how2play_custom(scene) != 1) {
        return (RET_ERR_MALLOC);
    }
    return (RET_OK);
}

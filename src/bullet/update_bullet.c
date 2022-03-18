/*
** EPITECH PROJECT, 2022
** defender
** File description:
** update bullet
*/

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include "defender_ennemy.h"
#include "list.h"
#include "my_bgs.h"
#include "defender_bullet.h"
#include "my_dico.h"

static int do_dmg_bully(bullet_t *bullet, list_ptr_t *list_bully)
{
    list_t *elem = NULL;
    object_t *obj = NULL;
    ennemy_t *ennemy = NULL;

    elem = list_bully->start;
    for (int i = 0; i < list_bully->len; i++, elem = elem->next) {
        obj = elem->var;
        ennemy = dico_t_get_value(obj->components, OBJ_COMP_ENNSTRUCT);
        if ((ennemy == NULL || ennemy->is_fly != bullet->is_fly) &&
                bullet->is_fly != 2) {
            continue;
        }
        ennemy->life -= bullet->dmg;
    }
    return (0);
}

static list_ptr_t *get_do_dmg_enn(object_t *obj, list_ptr_t *list_enn)
{
    list_t *elem = NULL;
    list_ptr_t *to_attack = NULL;
    sfFloatRect buf[2] = {0};
    object_t *target = NULL;

    to_attack = list_create();
    buf[0] = sfSprite_getGlobalBounds(obj->drawable.sprite);
    elem = list_enn->start;
    for (int i = 0; i < list_enn->len; i++, elem = elem->next) {
        target = elem->var;
        buf[1] = sfSprite_getGlobalBounds(target->drawable.sprite);
        if (sfFloatRect_intersects(&(buf[1]), &(buf[0]), NULL)) {
            list_add_to_start(to_attack, elem->var);
        }
    }
    return (to_attack);
}

static list_ptr_t *get_do_dmg(bullet_t *bullet, object_t *obj, scene_t *scene)
{
    list_ptr_t *list_enn = NULL;
    list_ptr_t *to_attack = NULL;
    sfFloatRect bullet_dir_size = {0};

    if (bullet == NULL || obj == NULL || scene == NULL) {
        return NULL;
    }
    list_enn = dico_t_get_value(scene->components, LIST_ENNEMY);
    if (list_enn == NULL) {
        return (NULL);
    }
    bullet_dir_size = sfSprite_getGlobalBounds(obj->drawable.sprite);
    if (sfFloatRect_contains(&bullet_dir_size, bullet->direction.x,
                bullet->direction.y) == sfFalse) {
        return (NULL);
    }
    to_attack = get_do_dmg_enn(obj, list_enn);
    return (to_attack);
}

static void move_bullet(object_t *obj, float dtime, bullet_t *bullet)
{
    float new_x = 0;
    float new_y = 0;
    float curr_x = 0;
    float curr_y = 0;

    if (obj == NULL || bullet == NULL) {
        return;
    }
    curr_x = obj->bigdata.sprite_bigdata.pos.x;
    curr_y = obj->bigdata.sprite_bigdata.pos.y;
    new_x = curr_x + (dtime * (bullet->direction.x -
                bullet->initial_position.x));
    new_y = curr_y + (dtime * (bullet->direction.y -
                bullet->initial_position.y));
    obj->bigdata.sprite_bigdata.pos.x = new_x;
    obj->bigdata.sprite_bigdata.pos.y = new_y;
}

void update_bullet(object_t *obj, scene_t *scene,
        __attribute__((unused)) window_t *win, float dtime)
{
    bullet_t *bullet = NULL;
    list_ptr_t *enn_to_bully = NULL;

    if (obj == NULL || scene == NULL || scene->pause == true) {
        return;
    }
    bullet = dico_t_get_value(obj->components, "DIRECTION BULLET");
    if (bullet == NULL) {
        return;
    }
    move_bullet(obj, dtime, bullet);
    enn_to_bully = get_do_dmg(bullet, obj, scene);
    if (enn_to_bully == NULL) {
        return;
    }
    do_dmg_bully(bullet, enn_to_bully);
    free_list(enn_to_bully);
    list_add_to_start(scene->to_remove, obj);
}

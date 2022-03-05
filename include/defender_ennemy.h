/*
** EPITECH PROJECT, 2022
** defender
** File description:
** ennemy
*/

#ifndef DEFENDER_ENNEMY_H_
    #define DEFENDER_ENNEMY_H_

    #include "defender.h"

    #define MAP_SIZE_SQUARE_X SQUARE_POS_INCREMENTATION
    #define MAP_SIZE_SQUARE_Y SQUARE_POS_INCREMENTATION
    #define MAP_ROAD_CHAR '#'
    #define MAP_SPAWN_CHAR 'S'

    #include <stdbool.h>
    #include "my_bgs.h"

static const char SCENE_COMP_MAP[] = "DEFENDER_MAP";
static const char OBJ_COMP_ENNSTRUCT[] = "ME_STRUCT_ENNEMY";
static const char OBJ_COMP_MANAGEWAVE[] = "MANAGE_WAVE";

struct ennemy_s {
    int xp;
    int com;
    int life;
    float speed;
    bool is_fly;
    float load_time;
    sfVector2i last_pos;
};
typedef struct ennemy_s ennemy_t;

void update_ennemy(object_t *obj, scene_t *scene, window_t *win, float dtime);

int create_ennemy(scene_t *scene, char const *path_json, int nb_spawn);

#endif
/*
** EPITECH PROJECT, 2022
** defender
** File description:
** ennemy
*/

#ifndef DEFENDER_ENNEMY_H_
    #define DEFENDER_ENNEMY_H_

    #define MAP_SIZE_SQUARE_X 48
    #define MAP_SIZE_SQUARE_Y 48
    #define MAP_ROAD_CHAR 'r'

    #include <stdbool.h>
    #include "my_bgs.h"

static const char SCENE_COMP_MAP[] = "DEFENDER_MAP";
static const char OBJ_COMP_ENNSTRUCT[] = "ME_STRUCT_ENNEMY";

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

int create_ennemy(scene_t *scene, char const *path_json, sfVector2f pos);

#endif

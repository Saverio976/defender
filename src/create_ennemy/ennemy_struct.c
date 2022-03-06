/*
** EPITECH PROJECT, 2022
** defender
** File description:
** ennemy structure fucntions
*/

#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include "my_strings.h"
#include "my_json.h"
#include "defender_ennemy.h"

static int set_ennemy_int(ennemy_t *enn, any_t *json)
{
    any_t *any = NULL;

    any = get_from_any(json, "d", "com");
    if (json == NULL || enn == NULL || any == NULL || any->type != INT) {
        return (0);
    }
    enn->com = any->value.i;
    any = get_from_any(json, "d", "xp");
    if (enn == NULL || any == NULL || any->type != INT) {
        return (0);
    }
    enn->xp = any->value.i;
    any = get_from_any(json, "d", "life");
    if (enn == NULL || any == NULL || any->type != INT) {
        return (0);
    }
    enn->life = any->value.i;
    return (1);
}

static int set_ennemy_float(ennemy_t *enn, any_t *json)
{
    any_t *any = NULL;

    any = get_from_any(json, "d", "speed");
    if (json == NULL || enn == NULL || any == NULL || any->type != FLOAT) {
        return (0);
    }
    enn->speed = any->value.f;
    any = get_from_any(json, "d", "load_time");
    if (any == NULL || any->type != FLOAT) {
        return (0);
    }
    enn->load_time = any->value.f;
    return (1);
}

static int set_ennemy_str(ennemy_t *enn, any_t *json)
{
    any_t *any = NULL;

    any = get_from_any(json, "d", "is_fly");
    if (any == NULL || any->type != STR) {
        return (0);
    }
    if (my_strcmp(any->value.str, "true") == 0) {
        enn->is_fly = true;
    } else {
        enn->is_fly = false;
    }
    return (1);
}

ennemy_t *init_ennemy(any_t *json)
{
    ennemy_t *enn = NULL;

    if (json == NULL) {
        return (NULL);
    }
    enn = malloc(sizeof(ennemy_t));
    if (enn == NULL || set_ennemy_int(enn, json) != 1) {
        return (NULL);
    }
    if (set_ennemy_float(enn, json) != 1) {
        return (NULL);
    }
    if (set_ennemy_str(enn, json) != 1) {
        return (NULL);
    }
    enn->last_pos = (sfVector2i) {-20, -20};
    return (enn);
}

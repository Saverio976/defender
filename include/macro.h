/*
** EPITECH PROJECT, 2022
** defender
** File description:
** macro
*/

#ifndef MACRO_H_
    #define MACRO_H_

    #include <stdbool.h>

enum trap_type {
    SPRINGBOARD_TYPE,
    POISON_TYPE
};

typedef struct tower_s tower_t;
typedef struct trap_s trap_t;

struct tower_s {
    int size;
    int cost;
    float fire_rate;
    float damage;
    int scope;
    bool is_anti_aircraft;
    float build_couldown;
};

struct trap_s {
    enum trap_type type;
    int cost;
    float dammage;
    int scope;
    float build_couldown;
};

//-----------------------------------------------------------------------------

static const tower_t STANDART = {
    4,
    4,
    1,
    1,
    6,
    false,
    2
};

static const tower_t AERIAN = {
    4,
    10,
    1 / 3,
    2,
    13,
    true,
    5
};

static const tower_t RAFFAL = {
    12,
    40,
    5,
    1 / 2,
    9,
    false,
    15
};

static const tower_t SNIPE = {
    8,
    50,
    1 / 5,
    5,
    18,
    false,
    30
};

//-----------------------------------------------------------------------------

static const trap_t SPRINGBOARD = {
    SPRINGBOARD_TYPE,
    7,
    1 / 2,
    0,
    0
};

static const trap_t POISON = {
    POISON_TYPE,
    25,
    1 / 5,
    4,
    10
};

#endif /* !MACRO_H_ */

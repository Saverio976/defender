/*
** EPITECH PROJECT, 2022
** defender
** File description:
** bullet related header
*/

#ifndef BULLET_H_
    #define BULLET_H

    #include <stdbool.h>
    #include <SFML/System/Vector2.h>

struct bullet_s {
    sfVector2f direction;
    bool is_fly;
};
typedef struct bullet_s bullet_t;

#endif

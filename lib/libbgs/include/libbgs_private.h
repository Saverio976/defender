/*
** EPITECH PROJECT, 2022
** libgs
** File description:
** private header file for the lib
*/

#ifndef BGS_PREIVATE_H_
    #define BGS_PREIVATE_H_

    #include <SFML/Graphics.h>
    #include "list.h"
    #include "my_bgs.h"

int event_handling(sfRenderWindow *win);

scene_t *get_scene_i(list_ptr_t *list, int i);

void object_update(object_t *object, dico_t *scene_components, window_t *win);

void display_sprite(object_t *object, dico_t *scene_components,
    dico_t *win_compoent, sfRenderWindow *win);

void display_text(object_t *object, dico_t *scene_components,
    dico_t *win_components, sfRenderWindow *win);

#endif

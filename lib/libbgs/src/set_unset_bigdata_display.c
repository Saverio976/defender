/*
** EPITECH PROJECT, 2022
** defender
** File description:
** set and unset bigdata display
*/

#include "my_bgs.h"
#include "my_bgs_components.h"

void sprite_set_display(object_t *object)
{
    if (object->type != SPRITE) {
        return;
    }
    object->bigdata.sprite_bigdata.display = true;
}

void sprite_unset_display(object_t *object)
{
    if (object->type != SPRITE) {
        return;
    }
    object->bigdata.sprite_bigdata.display = false;
}

void text_set_display(object_t *object)
{
    if (object->type != TEXT) {
        return;
    }
    object->bigdata.text_bigdata.display = true;
}

void text_unset_display(object_t *object)
{
    if (object->type != TEXT) {
        return;
    }
    object->bigdata.text_bigdata.display = false;
}

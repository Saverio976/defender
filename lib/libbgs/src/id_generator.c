/*
** EPITECH PROJECT, 2022
** defender
** File description:
** id_generator
*/

#include "my_strings.h"

char *get_id_generator(char dest[255])
{
    static unsigned char keys[255] = {0};
    static int index = 0;

    if (keys[index] >= 255) {
        index++;
    }
    if (index >= 255) {
        for (int i = 1; i < index; i++) {
            keys[i] = 0;
        }
        keys[0] += 1;
        index = 1;
    }
    keys[index] += 1;
    my_strcpy((char *) keys, dest);
    return (keys);
}

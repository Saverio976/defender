/*
** EPITECH PROJECT, 2022
** defender
** File description:
** check image pixel
*/

#include "my_bgs_components.h"
#include "my_bgs.h"

static void fill_arr(char **arr, sfUint8 *pixels, unsigned int x, unsigned int y)
{
    int cur_x = 0;
    int cur_y = 0;

    for (int i = 0; i < x * y * 4; i++) {
        if (cur_x >= x && cur_y < y) {
            cur_y += 1;
            arr[cur_y] = malloc(sizeof(char) * (x + 1));
            arr[cur_y][x];
        }
        arr[cur_y][cur_x++] = (pixels[i] == 0) ? '0' : '1';
    }
}

char **check_image_pixel(sfImage *image)
{
    const sfUint8 *pixels;
    sfVector2u size;
    char **arr = NULL;
    int raw_counter = 3;

    if (image == NULL) {
        return NULL;
    }
    pixels = sfImage_getPixelsPtr(image);
    size = sfImage_getSize(image);
    arr = malloc(sizeof(char *) * (size.y + 1));
    arr[size.y + 1] = NULL;
    if (arr == NULL) {
        return NULL;
    }
    fill_arr(arr, pixels, size.x, size.y);
    return (arr);
}

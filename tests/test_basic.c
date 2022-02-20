/*
** EPITECH PROJECT, 2021
** ...
** File description:
** basic criterion test
*/

#include <criterion/criterion.h>
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "libbgs_private.h"

Test(hitbox, check_image_pixel_empty)
{
    sfImage *image = sfImage_createFromFile("tests/hitbox/empty.png");
    char **arr = check_image_pixel(image);
    char **res = malloc(sizeof(char *) * 201); 

    for (int i = 0; i < 200; i++) {
        res[i] = malloc(sizeof(char) * 101);
        for (int x = 0; x < 100; x++) {
            res[i][x] = '0';
        }
        res[i][100] = '\0';
    }
    res[200] = NULL;
    for (int i = 0; i < 200; i++) {
        cr_assert_str_eq(res[i], arr[i]);
    }
}

Test(hitbox, check_image_pixel_fill)
{
    sfImage *image = sfImage_createFromFile("tests/hitbox/fill.png");
    char **arr = check_image_pixel(image);
    char **res = malloc(sizeof(char *) * 201); 

    for (int i = 0; i < 200; i++) {
        res[i] = malloc(sizeof(char) * (101));
        for (int x = 0; x < 100; x++) {
            res[i][x] = '1';
        }
        res[i][100] = '\0';
    }
    res[200] = NULL;
    for (int i = 0; i < 200; i++) {
        cr_assert_str_eq(res[i], arr[i]);
    }
}

Test(hitbox, find_higher_pixels_group_empty)
{
    sfImage *image = sfImage_createFromFile("tests/hitbox/empty.png");
    char **arr = check_image_pixel(image);
    sfFloatRect rect = find_higher_pixels_group(arr);

    cr_assert_eq(rect.height, 0);
    cr_assert_eq(rect.width, 0);
    cr_assert_eq(rect.top, 0);
    cr_assert_eq(rect.left, 0);
}

Test(hitbox, find_higher_pixels_group_fill)
{
    sfImage *image = sfImage_createFromFile("tests/hitbox/fill.png");
    char **arr = check_image_pixel(image);
    sfFloatRect rect = find_higher_pixels_group(arr);
    
    cr_assert_eq(rect.top, 0);
    cr_assert_eq(rect.width, 100);
    cr_assert_eq(rect.left, 0);
    cr_assert_eq(rect.height, 100);
    rect = find_higher_pixels_group(arr);
    cr_assert_eq(rect.top, 100);
    cr_assert_eq(rect.width, 100);
    cr_assert_eq(rect.left, 0);
    cr_assert_eq(rect.height, 100);
    rect = find_higher_pixels_group(arr);
    cr_assert_eq(rect.height, 0);
    cr_assert_eq(rect.left, 0);
    cr_assert_eq(rect.top, 0);
    cr_assert_eq(rect.width, 0);
}

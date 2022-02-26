/*
** EPITECH PROJECT, 2021
** ...
** File description:
** basic criterion test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_bgs.h"
#include "my_bgs_components.h"
#include "libbgs_private.h"
#include "my_fs.h"
#include "my_json.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static const char JSON_1[] = "tests/json/file_1.json";
static const char JSON_2[] = "tests/json/file_2.json";
static const char JSON_FLOAT[] = "tests/json/file_float_nb.json";
static const char JSON_NEG[] = "tests/json/file_neg_nb.json";

Test(json_parser, json_1, .init = redirect_all_std)
{
    char *file = fs_get_content(JSON_1);
    any_t *any = parse_json_file(JSON_1);

    cr_assert(file);
    cr_assert(any);
    prety_print(any);
    cr_assert_stdout_eq_str(file);
}

Test(json_parser, json_2, .init = redirect_all_std)
{
    char *file = fs_get_content(JSON_2);
    any_t *any = parse_json_file(JSON_2);

    cr_assert(file);
    cr_assert(any);
    prety_print(any);
    cr_assert_stdout_eq_str(file);
}

Test(json_parser, json_float, .init = redirect_all_std)
{
    char *file = fs_get_content(JSON_FLOAT);
    any_t *any = parse_json_file(JSON_FLOAT);

    cr_assert(file);
    cr_assert(any);
    prety_print(any);
    cr_assert_stdout_eq_str(file);
}

Test(json_parser, json_neg, .init = redirect_all_std)
{
    char *file = fs_get_content(JSON_NEG);
    any_t *any = parse_json_file(JSON_NEG);

    cr_assert(file);
    cr_assert(any);
    prety_print(any);
    cr_assert_stdout_eq_str(file);
}

/*
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

*/
/*
** EPITECH PROJECT, 2022
** writer json
** File description:
** write json
*/

#include "my_json.h"
#include "my_fs.h"

int write_json(any_t *any, char const *path)
{
    int fd = fs_open_ronly(path);
    //char str[] = "json\nwrite_test";

    if (any->type != DICT || fd < 0) {
        return RET_ERR_INPUT;
    }
    //write(fd, str, 9);
    return RET_OK;
}

/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** my_others
*/

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libmy_malloc.h"

void free(void *ptr)
{
    t_block tmp;

    if (ptr == NULL)
        return;
    tmp = (void *)ptr - BLOCK_SIZE;
    tmp->usable = true;
}

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = NULL;

    ptr = malloc(size * nmemb);
    memset(ptr, 0, size * nmemb);
    return ptr;
}

void *realloc(void *ptr, size_t size)
{
    void *save = ptr;
    t_block save_header = (void *)save - BLOCK_SIZE;

    if (!ptr){
        return malloc(size);
    }
    if (size == 0 && ptr) {
        free(ptr);
        return NULL;
    }
    free(ptr);
    ptr = malloc(size);
    if (save_header->size > size)
        ptr = memcpy(ptr, save, size);
    else if (save_header->size < size)
        ptr = memcpy(ptr, save, save_header->size);
    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    ptr = realloc(ptr, nmemb * size);
    return ptr;
}
/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** malloc
*/

#ifndef MALLOC_H_
#define MALLOC_H_
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define BLOCK_SIZE 32

typedef struct s_block *t_block;

struct s_block  {
    size_t size;
    t_block next;
    bool usable;
};

t_block b;
void *malloc (size_t size);
void free (void *ptr);
void *calloc (size_t nmemb, size_t size);
void *realloc (void *ptr, size_t size);
void *reallocarray (void *ptr, size_t nmemb, size_t size);
#endif /* !MALLOC_H_ */

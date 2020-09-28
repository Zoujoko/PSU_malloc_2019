/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** my_malloc
*/
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libmy_malloc.h"

size_t amount_of_pages(size_t size)
{
    size_t pages = getpagesize() * 2;

    while (pages < size + (BLOCK_SIZE * 2)) {
        pages += (getpagesize() * 2);
    }
    return pages;
}

size_t align_pointers(size_t size)
{
    if (size % 2 != 0)
        return size + 1;
    return size;
}

void extend_heap(size_t size)
{
    t_block tmp = b;

    if (!b) {
        b = sbrk(0);
        if (b == (void *) -1)
            return;
        sbrk(amount_of_pages(size));
        return;
    }
    sbrk(amount_of_pages(size));
    for (; tmp->next; tmp = tmp->next);
    tmp->size += amount_of_pages(size);
    return;
}

void *create_node(size_t size)
{
    t_block tmp = b;

    if (!b->next) {
        b->size = size;
        b->usable = false;
        b->next = (void *)b + BLOCK_SIZE + size;
        b->next->size = amount_of_pages(size) - BLOCK_SIZE - size;
        b->next->usable = true;
        b->next->next = NULL;
        return (void *)b + BLOCK_SIZE;
    }
    for (; tmp->next; tmp = tmp->next);
    if (!(tmp->size > size + BLOCK_SIZE))
        extend_heap(size);
    tmp->usable = true;
    tmp->next = (void *)tmp + BLOCK_SIZE + size;
    tmp->next->usable = false;
    tmp->next->next = NULL;
    tmp->next->size = tmp->size - BLOCK_SIZE - size;
    tmp->size = size;
    return (void *)tmp + BLOCK_SIZE;
}

void *malloc(size_t size)
{
    t_block save = b;

    size = align_pointers(size);
    if (!b) {
        extend_heap(size);
        return create_node(size);
    }
    for (; save->next ; save = save->next) {
        if (save->usable == false && save->size == size) {
            return (void *)save + BLOCK_SIZE;
        }
    }
    return create_node(size);
}
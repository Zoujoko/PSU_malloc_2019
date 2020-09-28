/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** criterion
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdlib.h>

Test(mallocing_test, amount_of_pages)
{
    void *handle = dlopen("libmy_malloc.so", RTLD_LAZY);
    size_t (*ptr)(size_t);
    char *error;

    if (!handle) {
        fprintf(stderr, "Can't find the libmy_malloc.so library\n");
        return;
    }
    * (void **) (&ptr) = dlsym(handle, "amount_of_pages");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        return;;
    }
    dlerror();
    cr_assert((*ptr)(1) == getpagesize() * 2);
    cr_assert((*ptr)(getpagesize() * 2 + 3) == getpagesize() * 4);
    dlclose(handle);
}

Test(mallocing_test, align_pointers)
{
    void *handle = dlopen("libmy_malloc.so", RTLD_LAZY);
    size_t (*ptr)(size_t);
    char *error;

    if (!handle) {
        fprintf(stderr, "Can't find the libmy_malloc.so library\n");
        return;
    }
    * (void **) (&ptr) = dlsym(handle, "align_pointers");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        return;;
    }
    dlerror();
    cr_assert((*ptr)(1) == 2);
    cr_assert((*ptr)(2) == 2);
    dlclose(handle);
}
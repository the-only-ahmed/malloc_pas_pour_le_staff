/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 18:32:58 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:29:51 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*getLarge(size_t size) {
    t_block		*large;
    t_block		*tmp;

    large = (t_block*)allocate(sizeof(t_block));
    if (!large)
        return (NULL);
    large->addr = allocate(size);
    large->size = size;
    large->next = NULL;
    if (!g_memory.large) {
        large->prev = NULL;
        g_memory.large = large;
    } else {
        tmp = g_memory.large;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = large;
        large->prev = tmp;
    }
    return (large->addr);
}

#include <stdio.h>

void    *tiny(size_t size) {
    static int  used_memory = 0;
    const int  max_size = TINY_M * getpagesize();
    static void *pool = NULL;
    void        *ptr;

    printf("size : %zu, used size : %d, ", size, used_memory);
    used_memory += size;
    printf("new used size : %d ==> %d\n", used_memory, max_size);
    used_memory += size;
    if (!pool || used_memory >= max_size) {
        used_memory = size;
        pool = allocate(max_size);
    }
    ptr = pool;
    pool += size;
    return ptr;
}

void    *small(size_t size) {
    static int  used_memory = 0;
    const int  max_size = SMALL_M * getpagesize();
    static void *pool = NULL;
    void        *ptr;

    used_memory += size;
    if (!pool || used_memory >= max_size) {
        used_memory = size;
        pool = allocate(max_size);
    }
    ptr = pool;
    pool += size;
    return ptr;
}

void    *getTinyOrSmall(char type, size_t size) {
    void        *ptr;
    t_block     *block;
    t_block     *tmp;

    ptr = (type == TINY) ? tiny(size) : small(size);
    if (!ptr)
        return (ptr);
    block = (t_block*)allocate(sizeof(t_block));
    if (!block)
        return (NULL);
    block->addr = ptr;
    block->size = size;
    block->next = NULL;
    block->prev = NULL;
    if (!g_memory.tiny && type == TINY)
        g_memory.tiny = block;
    else if (!g_memory.small && type == SMALL)
        g_memory.small = block;
    else {
        tmp = (type == TINY) ? g_memory.tiny :g_memory.small;
        while (tmp->next)
            tmp = tmp->next;
        block->prev = tmp;
        tmp->next = block;
    }
    return (ptr);
}

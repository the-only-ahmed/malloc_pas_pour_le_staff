/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 18:32:58 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/10 22:58:11 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <errno.h>

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

void    *tiny(size_t size) {
	static int  used_memory = 0;
	static void *pool = NULL;
	int  max_size;
	void        *ptr;

	max_size = TINY_M * getpagesize();
	if (!pool || used_memory >= max_size) {
		used_memory = 0;
		pool = allocate(max_size);
		if (!pool)
			return (NULL);
	}
	ptr = &(pool[used_memory]);
	used_memory += size;
//	ptr = pool;
//	pool += size;
	return ptr;
}

void    *small(size_t size) {
	static int  used_memory = 0;
	static void *pool = NULL;
	int  max_size;
	void        *ptr;

	max_size = SMALL_M * getpagesize();
	if (!pool || used_memory >= max_size) {
		used_memory = 0;
		pool = allocate(max_size);
		if (!pool)
			return (NULL);
	}
	ptr = &(pool[used_memory]);
	used_memory += size;
	//ptr = pool;
	//pool += size;
	return ptr;
}

t_block		*createBlock(void *ptr, size_t size, char type) {
	static void		*block_pool = NULL;
	static int		used_pool = 0;
	t_block			*block;

	if (!block_pool || used_pool + sizeof(t_block) >= 512 * sizeof(t_block))
	{
		used_pool = 0;
		block_pool = allocate(sizeof(t_block) * 512);
	}
	block = &(block_pool[used_pool]);
	used_pool += sizeof(t_block) + 1;
	if (block == MAP_FAILED)
		return (NULL);
	return (block);
}

void    *getTinyOrSmall(char type, size_t size) {
	void        *ptr;
	t_block     *block;
	t_block     *tmp;

	ptr = (type == TINY) ? tiny(size) : small(size);
	if (!ptr)
		return (NULL);
	block = createBlock(ptr, size, type);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 17:47:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/10 22:14:29 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block  *getBlock(void *ptr, t_block *block) {
	while (block) {
		if (block->addr == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

static t_block  *checkIfExists(void *ptr) {
	t_block     *block;

	if ((block = getBlock(ptr, g_memory.tiny)) != NULL)
		return (block);
	if ((block = getBlock(ptr, g_memory.small)) != NULL)
		return (block);
	if ((block = getBlock(ptr, g_memory.large)) != NULL)
		return (block);
	return (NULL);
}

void    *realloc(void *ptr, size_t size) {
	t_block     *block;
	void         *tmp;

	write(1, "realloc\n", 8);
	if (!ptr && size != 0)
		return (malloc(size));
	else if (!ptr && size == 0)
		return (NULL);
	else {
		block = checkIfExists(ptr);
		if (block) {
			if (size == 0)
				free(ptr);
			else if (size <= block->size)
				return (ptr);
			else {
				tmp = malloc(size);
				ft_memcpy(tmp, ptr, block->size);
				return (tmp);
			}
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:39:53 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/11 19:27:31 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*allocate(size_t size)
{
	void	*ptr;

	ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

static void		*get_ptr(size_t size, t_block *block)
{
	while (block)
	{
		if (block->size == size && !block->is_in_use)
		{
			block->is_in_use = 1;
			return (block->addr);
		}
		block = block->next;
	}
	return (NULL);
}

static void		*check_if_exists(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size <= TINY_S)
		ptr = get_ptr(size, g_memory.tiny);
	else if (size <= SMALL_S)
		ptr = get_ptr(size, g_memory.small);
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ptr;

	if ((ptr = check_if_exists(size)) != NULL)
		return (ptr);
	if (size <= TINY_S)
		ptr = get_tiny_or_small(TINY, size);
	else if (size <= SMALL_S)
		ptr = get_tiny_or_small(SMALL, size);
	else
		ptr = get_large(size);
	return (ptr);
}

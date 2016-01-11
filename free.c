/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 19:07:13 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/11 18:53:12 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block		*check_if_exists(void *ptr, t_block *block)
{
	while (block)
	{
		if (ptr == block->addr)
		{
			block->isInUse = 0;
			return (block);
		}
		block = block->next;
	}
	return (NULL);
}

static void			erase_block(t_block *tmp)
{
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
}

void				free(void *ptr)
{
	t_block		*tmp;

	if (!ptr)
		return ;
	if ((tmp = check_if_exists(ptr, g_memory.tiny)) != NULL)
		return ;
	if ((tmp = check_if_exists(ptr, g_memory.small)) != NULL)
		return ;
	if ((tmp = check_if_exists(ptr, g_memory.large)) != NULL)
	{
		munmap(ptr, tmp->size);
		if (tmp == g_memory.large)
		{
			g_memory.large = tmp->next;
			if (g_memory.large)
				g_memory.large->prev = NULL;
		}
		else
			erase_block(tmp);
		munmap(tmp, sizeof(t_block));
	}
}

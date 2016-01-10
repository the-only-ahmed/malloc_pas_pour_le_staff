/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 19:07:13 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:29:38 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block     *checkIfExists(void *ptr, t_block *block) {
    while (block) {
        if (ptr == block->addr) {
            munmap(ptr, block->size);
            return (block);
        }
        block = block->next;
    }
    return (NULL);
}

void        eraseBlock(t_block *tmp) {
    if (tmp->next)
        tmp->next->prev = tmp->prev;
    if (tmp->prev)
        tmp->prev->next = tmp->next;
}

void	    free(void *ptr) {
    t_block		*tmp;
    
    if ((tmp = checkIfExists(ptr, g_memory.tiny)) != NULL) {
        if (tmp == g_memory.tiny) {
            g_memory.tiny = tmp->next;
            if (g_memory.tiny)
                g_memory.tiny->prev = NULL;
        } else
            eraseBlock(tmp);
        munmap(tmp, sizeof(t_block));
        return;
    }
    if ((tmp = checkIfExists(ptr, g_memory.small)) != NULL) {
        if (tmp == g_memory.small) {
            g_memory.small = tmp->next;
            if (g_memory.small)
                g_memory.small->prev = NULL;
        } else
            eraseBlock(tmp);
        munmap(tmp, sizeof(t_block));
        return;
    }
    if ((tmp = checkIfExists(ptr, g_memory.large)) != NULL) {
        if (tmp == g_memory.large) {
            g_memory.large = tmp->next;
            if (g_memory.large)
                g_memory.large->prev = NULL;
        } else
            eraseBlock(tmp);
        munmap(tmp, sizeof(t_block));
    }
}

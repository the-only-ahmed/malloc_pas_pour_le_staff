/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 17:53:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:03:39 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*allocate(size_t size) {
    void	*ptr;

    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED)
        return (NULL);
    return (ptr);
}

void	*malloc(size_t size) {
    void	*ptr;

    if (size <= TINY_S)
        ptr = getTinyOrSmall(TINY, size);
    else if (size <= SMALL_S)
        ptr = getTinyOrSmall(SMALL, size);
    else
        ptr = getLarge(size);
    return (ptr);
}

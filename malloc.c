/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 17:53:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/10 22:49:36 by ael-kadh         ###   ########.fr       */
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

#include <stdio.h>

void	*malloc(size_t size) {
	void	*ptr;

	write(1, "malloc : ", 9);
	ft_putnbr_base(size, 10);
	write(1, "\n", 1);
	if (size <= TINY_S)
		ptr = getTinyOrSmall(TINY, size);
	else if (size <= SMALL_S)
		ptr = getTinyOrSmall(SMALL, size);
	else
		ptr = getLarge(size);
	write(1, "malloc : ", 9);
	ft_putnbr_base(size, 10);
	write(1, " ==> ", 5);
	if (ptr)
		ft_putnbr_base((size_t)ptr, 16);
	write(1, "\n", 1);
	return (ptr);
}

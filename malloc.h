/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 17:47:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2016/01/09 19:21:34 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <sys/mman.h>

# define TINY 't'
# define SMALL 's'
# define LARGE 'l'

# define TINY_S 500
# define SMALL_S 4096

# define TINY_M 150
# define SMALL_M 500

typedef struct	    s_block {
    void	    *addr;
    size_t	    size;
    struct s_block  *next;
    struct s_block  *prev;
}		    t_block;

typedef struct	    s_malloc {
    t_block         *tiny;
    t_block         *small;
    t_block         *large;
}		    t_malloc;

t_malloc g_memory;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void    show_alloc_mem();
void	*getTinyOrSmall(char type, size_t size);
void	*getLarge(size_t size);
void	*allocate(size_t size);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	ft_putstr(char const *str);
void	ft_putnbr_base(unsigned int n, unsigned int base);

#endif

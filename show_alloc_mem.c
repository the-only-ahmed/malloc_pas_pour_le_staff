#include "malloc.h"

static void    show_block(t_block *block) {
	size_t     size;

	size = block->size;
	ft_putstr("0x");
	ft_putnbr_base((size_t)block->addr, 16);
	ft_putstr(" - 0x");
	ft_putnbr_base((size_t)block->addr + size, 16);
	ft_putstr(" : ");
	ft_putnbr_base(size, 10);
	ft_putstr(" octets\n");
}

static size_t   show_memory(t_block *block, char *type) {
	size_t    size;

	size = 0;
	ft_putstr(type);
	if (!block) {
		ft_putstr("is empty\n");
		return (0);
	}
	ft_putstr("0x");
	ft_putnbr_base((size_t)block->addr, 16);
	write(1, "\n", 1);
	while (block) {
		size += block->size;
		show_block(block);
		block = block->next;
	}
	return (size);
}

void    show_alloc_mem() {
	size_t    total_size;

	total_size = 0;
	total_size += show_memory(g_memory.tiny, "TINY : ");
	total_size += show_memory(g_memory.small, "SMALL : ");
	total_size += show_memory(g_memory.large, "LARGE : ");
	ft_putstr("Total : ");
	ft_putnbr_base(total_size, 10);
	ft_putstr(" octets\n");
}

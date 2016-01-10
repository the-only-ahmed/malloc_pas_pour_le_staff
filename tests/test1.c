#include "malloc.h"

int		main() {
	int i = 0;
	char *addr;

	while (i < 1024) {
		addr = (char*)ft_malloc(1024);
		addr[0] = 42;
		i++;
	}
	return 0;
}

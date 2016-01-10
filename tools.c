#include "malloc.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
    int		i;
    char	*ss1;
    const char	*ss2;

    i = 0;
    ss1 = s1;
    ss2 = s2;
    while (n > 0)
    {
        ss1[i] = ss2[i];
        n--;
        i++;
    }
    return (ss1);
}

void	ft_putstr(char const *str)
{
    int	    i;

    i = 0;
    while (str[i] != '\0')
        write(1, &str[i++], 1);
    i++;
}

void	ft_putnbr_base(unsigned int n, unsigned int base)
{
    char	*val;

    val = "0123456789ABCDEF";
    if (base < 2 || base > 16)
        return ;
    if (n / base != 0)
    {
        ft_putnbr_base(n / base, base);
        write(1, &val[n % base], 1);
    }
    else
        write(1, &val[n % base], 1);
}

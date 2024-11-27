#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	tmp;
	unsigned char	*tmp2;

	tmp = (unsigned char)c;
	tmp2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tmp2[i] = tmp;
		i++;
	}
	return (s);
}

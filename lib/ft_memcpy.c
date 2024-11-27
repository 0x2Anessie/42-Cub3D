#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	register size_t			i;
	register const size_t	size = sizeof(size_t);

	i = 0;
	if (n > size)
	{
		while (i < n - size)
		{
			*(size_t *)(dest + i) = *(size_t *)(src + i);
			i += size;
		}
	}
	while (i != n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}

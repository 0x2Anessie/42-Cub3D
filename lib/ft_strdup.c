#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen((char *)s);
	res = ft_calloc(sizeof(char), len + 1);
	if (res == 0)
		return (0);
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

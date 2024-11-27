#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(new_size, 1);
	if (!new_ptr)
		return (NULL);
	if (prev_size > new_size)
		prev_size = new_size;
	ft_memcpy(new_ptr, ptr, prev_size);
	free(ptr);
	return (new_ptr);
}

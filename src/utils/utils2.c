#include "../../include/cub3d.h"

t_intvector	get_map_size(int fd, char *line, bool *error)
{
	t_intvector	len;

	*error = false;
	len = (t_intvector){0};
	while (line != NULL)
	{
		if (line[0] == '\n')
			break ;
		rmv_final_whitespace(line);
		if (len.x < (int)ft_strlen(line))
			len.x = ft_strlen(line);
		len.y++;
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		if (line[0] != '\n')
			*error = true;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (len);
}

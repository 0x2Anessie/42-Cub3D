#include "../../include/cub3d.h"

void	get_data_address(t_image *image, t_intvector size)
{
	if (!image)
		return ;
	image->addr = mlx_get_data_addr(image->img, &image->opp,
			&image->size_line, &image->endian);
	image->opp /= 8;
	image->size = size;
}

enum e_orientation	get_wall_orientation(t_player player, t_vector wall)
{
	if ((wall.x - (int)wall.x) != 0)
	{
		if (player.chunk_pos.y > wall.y)
			return (e_north);
		else
			return (e_south);
	}
	else
	{
		if (player.chunk_pos.x > wall.x)
			return (e_west);
		else
			return (e_east);
	}
}

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

int	next_whitespace(char *line, int i)
{
	while (line[i] != '\0' && !(line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\v' || line[i] == '\n' || line[i] == '\f'
			|| line[i] == '\r'))
		i++;
	return (i);
}

void	rmv_final_whitespace(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i <= 0)
		return ;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r'))
		i--;
	if (i + 1 < ft_strlen(str))
		str[i + 1] = '\0';
	return ;
}

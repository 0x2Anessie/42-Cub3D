#include "../../include/cub3d.h"

static char	**map_init(t_intvector len)
{
	int		i;
	char	**res;

	i = 0;
	res = ft_calloc(len.y, sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (i < len.y)
	{
		res[i] = ft_calloc(len.x, sizeof(char));
		if (res[i] == NULL)
			return (free_tab(res, len.y), NULL);
		i++;
	}
	return (res);
}

bool	create_map(t_game *game, int fd, char *line)
{
	bool	error;

	game->map_size = get_map_size(fd, line, &error);
	if (game->map_size.x == 0 || game->map_size.y == 0)
		return (print_error("Empty map\n", 1), false);
	if (error == true)
		return (print_error("Unknown element in map.\n", 1), false);
	game->map = map_init(game->map_size);
	if (game->map == NULL)
		return (print_error(NULL, 0), false);
	return (true);
}

bool	parse_map(char *filename, t_game *game, int nb_line)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error(NULL, 0), false);
	line = get_next_line(fd);
	i = -1;
	while (line != NULL && ++i < nb_line)
	{
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (line != NULL && ++i < game->map_size.y)
	{
		rmv_final_whitespace(line);
		ft_memcpy(game->map[i], line, ft_strlen(line));
		ft_memset(game->map[i] + (ft_strlen(line)), ' ',
			game->map_size.x - ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	return (free(line), close(fd), true);
}

static bool	_check_sides(char **map, int x, int y, t_intvector map_size)
{
	if (x == 0 || y == 0 || x == map_size.x - 1 || y == map_size.y - 1)
		return (false);
	if (map[y - 1][x] == ' ' || map[y][x - 1] == ' '
			|| map[y + 1][x] == ' ' || map[y][x + 1] == ' ')
		return (false);
	return (true);
}

bool	check_map(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	y = 0;
	while (y < game->map_size.y)
	{
		x = 0;
		while (x < game->map_size.x)
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
				&& map[y][x] != 'W' && map[y][x] != 'S' && map[y][x] != 'E'
				&& map[y][x] != ' ')
				return (print_error("Unknown character in map.\n", 1), false);
			if (map[y][x] == '0')
			{
				if (!_check_sides(map, x, y, game->map_size))
					return (print_error("Map must be closed.\n", 1), false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

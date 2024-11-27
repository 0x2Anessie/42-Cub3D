#include "../../include/cub3d.h"

static bool	get_texture(t_game *game, char *str, enum e_images orient)
{
	char	*filename;
	int		i;
	int		len;

	if (game->filename[orient] != NULL)
		return (print_error("Multiple definition of texture\n", 1), false);
	i = skip_whitespace(str);
	len = ft_strlen(str + i);
	if (len >= 1 && str[i + len - 1] == '\n')
		str[i + len - 1] = '\0';
	filename = ft_strdup(str + i);
	if (filename == NULL)
		return (print_error("Malloc failed\n", 1), false);
	game->filename[orient] = filename;
	return (true);
}

static bool	texture_cmp(char *line, t_game *game, int i)
{
	int	next_wsp;

	next_wsp = next_whitespace(line, i);
	if (next_wsp - i == 1)
	{
		if (line[i] == 'F')
			return (find_color(line + i + 1, game, 'F'));
		else if (line[i] == 'C')
			return (find_color(line + i + 1, game, 'C'));
	}
	else if (next_wsp - i == 2)
	{
		if (ft_strncmp(line + i, "NO", 2) == 0)
			return (get_texture(game, line + i + 2, e_north_wall));
		else if (ft_strncmp(line + i, "SO", 2) == 0)
			return (get_texture(game, line + i + 2, e_south_wall));
		else if (ft_strncmp(line + i, "WE", 2) == 0)
			return (get_texture(game, line + i + 2, e_west_wall));
		else if (ft_strncmp(line + i, "EA", 2) == 0)
			return (get_texture(game, line + i + 2, e_east_wall));
	}
	return (print_error("Invalid identifier\n", 1), false);
}

static bool	texture(t_game *game, char **line, int fd)
{
	int		i;

	i = skip_whitespace(*line);
	if (ft_strlen(*line + i) < 1)
		return (print_error("Line too short\n", 1), free(*line),
			false);
	if (!texture_cmp(*line, game, i))
		return (free(*line), false);
	free(*line);
	*line = get_next_line(fd);
	return (true);
}

bool	parse_texture(int fd, t_game *game, int *nb_line, char **rest)
{
	char	*line;
	int		cpt_texture;

	cpt_texture = 0;
	(*nb_line) = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		(*nb_line)++;
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!texture(game, &line, fd))
			return (false);
		if (++cpt_texture == 6)
			break ;
	}
	if (cpt_texture != 6)
		return (print_error("Missing texture\n", 1), false);
	*rest = line;
	return (true);
}

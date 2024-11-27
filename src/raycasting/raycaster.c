#include "../../include/cub3d.h"

static const int	g_half_screen = WIN_X * WIN_Y / 2 * 4;

// __attribute__((always_inline))
static inline double	dist(t_game *game, double x, double y, double angle)
{
	t_vector	delta;
	double		res;

	delta.x = fabs(x - game->player->chunk_pos.x);
	delta.y = fabs(y - game->player->chunk_pos.y);
	res = sqrt((delta.x * delta.x + delta.y * delta.y))
		* cos(angle * DEG_TO_RADIAN);
	if (res == 0)
		return (0.1);
	return (res);
}

// __attribute__((always_inline))
static inline void	draw_floor_ceiling(t_game *game)
{
	ft_memcpy(game->image->addr,
		game->tab_images[e_ceiling]->addr, g_half_screen);
	ft_memcpy(game->image->addr + g_half_screen,
		game->tab_images[e_floor]->addr, g_half_screen);
}

void	raycasting(t_game *game)
{
	int			x;
	double		height;
	double		angle;
	t_vector	wall;
	t_vector	fpos;

	draw_floor_ceiling(game);
	fpos = game->player->chunk_pos;
	x = -WIN_X / 2;
	while (x < WIN_X / 2)
	{
		angle = atanf(x / game->consts) * 180 / M_PI;
		if (game->player->angle + angle >= 360)
			angle = angle - 360;
		if (game->player->angle + angle < 0)
			angle = angle + 360;
		wall = get_wall_hit(fpos, game->map,
				game->player->angle + angle, game->map_size);
		if (wall.x == -1 && wall.y == -1)
			height = 0;
		else
			height = 1 / dist(game, wall.x, wall.y, angle) * game->consts;
		draw_vertical(game, x + WIN_X / 2, wall, height);
		x++;
	}
}

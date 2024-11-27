#include "../../include/cub3d.h"

// __attribute__((always_inline))
static inline unsigned int	get_color_at(char *addr, int size_line,
		int x, int y)
{
	return (*(int *)(addr + (y * size_line + x * 4)));
}

// __attribute__((always_inline))
static inline void	my_mlx_pixel_put(char *addr, int size_line, t_intvector pos,
		int color)
{
	*(int *)(addr + (pos.y * size_line + pos.x * 4)) = color;
}

static t_image	*get_draw_info(t_game *game, t_draw *draw, double height,
		t_vector wall)
{
	enum e_orientation	orient;
	t_image				*image;

	draw->y_begin = WIN_Y / 2.0 - (int)(height / 2);
	draw->y_end = WIN_Y / 2.0 + ((int)height - (int)(height / 2));
	if (height != 0)
	{
		orient = get_wall_orientation(*(game->player), wall);
		image = game->tab_images[orient];
		draw->img_y_diff = image->size.y / height;
		if (draw->y_begin < 0)
		{
			draw->img.y = -draw->y_begin * draw->img_y_diff;
			draw->y_begin = 0;
		}
		if (draw->y_end > WIN_Y)
			draw->y_end = WIN_Y;
		if (orient == e_north || orient == e_south)
			draw->img.x = (wall.x - (int)wall.x) * image->size.x;
		else
			draw->img.x = (wall.y - (int)wall.y) * image->size.x;
		if (orient == e_west || orient == e_south)
			draw->img.x = image->size.x - draw->img.x - 1;
	}
	return (image);
}

void	draw_vertical(t_game *game, int x, t_vector wall, double height)
{
	t_draw		draw_info;
	t_image		*image;
	int			y_begin;
	t_vector	img;

	draw_info.img.y = 0;
	image = get_draw_info(game, &draw_info, height, wall);
	y_begin = draw_info.y_begin;
	img = draw_info.img;
	while (y_begin < draw_info.y_end)
	{
		my_mlx_pixel_put(game->image->addr, game->image->size_line,
			(t_intvector){x, y_begin},
			get_color_at(image->addr, image->size_line, img.x, img.y));
		img.y += draw_info.img_y_diff;
		y_begin++;
	}
}

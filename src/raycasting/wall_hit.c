#include "../../include/cub3d.h"

static t_intvector	get_sign(double angle)
{
	t_intvector	sign;

	if (angle >= 0 && angle <= 180)
		sign.x = 1;
	else
		sign.x = -1;
	if (angle >= 90 && angle <= 270)
		sign.y = 1;
	else
		sign.y = -1;
	return (sign);
}

t_vector	get_wall_hit(t_vector fpos, char **map, float angle,
		t_intvector map_size)
{
	t_intvector	sign;

	if (fpos.x < 0 || fpos.y < 0 || fpos.x > map_size.x || fpos.y > map_size.y)
		return ((t_vector){-1, -1});
	sign = get_sign(angle);
	angle = fabs(tan(angle * DEG_TO_RADIAN));
	if (sign.x == 1 && sign.y == 1)
		return (get_wall_hit_se(fpos, map, angle, map_size));
	else if (sign.x == 1 && sign.y == -1)
		return (get_wall_hit_ne(fpos, map, angle, map_size));
	else if (sign.x == -1 && sign.y == 1)
		return (get_wall_hit_sw(fpos, map, angle, map_size));
	else
		return (get_wall_hit_nw(fpos, map, angle));
	return ((t_vector){0});
}

#include "../../include/cub3d.h"

/*
inline: Suggests to the compiler that the function should be inlined.
When a function is inlined, the compiler replaces the function call with the
function's code at the point of invocation, eliminating the overhead
of a function call.
__attribute__((always_inline)): This is a GCC and Clang-specific attribute
that forces the compiler to inline the function, even if it would otherwise
decide not to due to the function's size or complexity. Normally, the
compiler may ignore inline if inlining the function is not deemed
beneficial, but always_inline overrides this behavior.
*/

// __attribute__((always_inline))
static inline t_vector	find_wall(t_map map, t_vector comp,
		t_vector step, t_intvector map_pos)
{
	while (true)
	{
		if (map_pos.y >= comp.y)
		{
			if (map_pos.x - 1 < 0)
				return ((t_vector){-1, -1});
			if (map.map[(int)(comp.y)][map_pos.x - 1] == '1')
				return ((t_vector){map_pos.x, comp.y});
			comp.y += step.y;
			map_pos.x += -1;
		}
		else
		{
			if ((int)(comp.x) < 0 || map_pos.y >= map.map_size.y)
				return ((t_vector){-1, -1});
			if (map.map[map_pos.y][((int)(comp.x))] == '1')
				return ((t_vector){comp.x, map_pos.y});
			comp.x += step.x;
			map_pos.y += 1;
		}
	}
}

// SW
// X (-1)
// Y (1)
t_vector	get_wall_hit_sw(t_vector fpos,
								char **map, float angle, t_intvector map_size)
{
	t_vector	step;
	t_vector	comp;
	t_intvector	map_pos;

	map_pos = (t_intvector){(int)fpos.x, (int)fpos.y + 1};
	comp.x = fpos.x + fabs(fpos.y - map_pos.y) * angle * -1;
	comp.y = fpos.y + fabs(fpos.x - map_pos.x) / angle;
	step = (t_vector){angle * -1, 1 / angle};
	if ((int)(fpos.y) >= map_size.y)
		return ((t_vector){-1, -1});
	return (find_wall((t_map){map, map_size}, comp, step, map_pos));
}

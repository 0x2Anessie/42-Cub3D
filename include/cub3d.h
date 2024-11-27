#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************ */
/*								Includes									*/
/* ************************************************************************ */

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>

# include "../lib/libft.h"
# include"../minilibx-linux/mlx.h"

/* ************************************************************************	*/
/*								Defines										*/
/* ************************************************************************	*/

//	GAME
# define WIN_X 1920 //1920 - 918
# define WIN_Y 1080 //1080 - 468
# define CHUNK_SIZE 20
# define FOV 85
# define MOUV 1.5
# define ROTATION 3.2
# define SPEED 2.5

// KEYS
# define ESC 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

// MATHS
# define DEG_TO_RADIAN .0174532
# define DIAG_PYTHAGORE .707

/* ************************************************************************	*/
/*								  Enum  									*/
/* ************************************************************************	*/

enum e_orientation
{
	e_north = 0,
	e_east,
	e_south,
	e_west
};

enum e_images
{
	e_north_wall,
	e_east_wall,
	e_south_wall,
	e_west_wall,
	e_ceiling,
	e_floor
};

/* ************************************************************************	*/
/*								Structures									*/
/* ************************************************************************	*/

// typedef struct s_			t_;

typedef struct s_intvector		t_intvector;
typedef struct s_vector			t_vector;
typedef struct s_map			t_map;
typedef struct s_player			t_player;
typedef struct s_image			t_image;
typedef struct s_draw			t_draw;
typedef struct s_game			t_game;

struct s_intvector
{
	int					x;
	int					y;
};

struct s_vector
{
	double				x;
	double				y;
};

struct s_map
{
	char				**map;
	t_intvector			map_size;
};

struct s_player
{
	t_intvector			pos;
	t_intvector			dir;
	int					view;
	double				angle;
	t_vector			chunk_pos;
	t_vector			vector_pos;
};

struct s_image
{
	int					opp;
	void				*img;
	char				*addr;
	int					endian;
	int					size_line;
	t_intvector			size;
};

struct s_draw
{
	t_vector			img;
	int					y_end;
	int					y_begin;
	double				img_y_diff;
};

struct s_game
{
	void				*mlx_ptr;
	void				*win_ptr;
	char				**map;
	char				**filename;
	double				consts;
	unsigned int		floor_rgb;
	unsigned int		ceiling_rgb;
	t_intvector			map_size;
	t_player			*player;
	t_image				*image;
	t_image				**tab_images;
};

/* ************************************************************************	*/
/*								Prototypes									*/
/* ************************************************************************	*/

int						main(int argc, char **argv);

// ------------ Utils ------------
void					get_data_address(t_image *image, t_intvector size);
enum e_orientation		get_wall_orientation(t_player player, t_vector wall);
int						skip_whitespace(char *str);
int						next_whitespace(char *line, int i);
void					rmv_final_whitespace(char *str);

// --------- Print & Free --------
int						ft_close(t_game *game);
void					free_tab(char **str, int sizey);
void					destroy_all_images(t_game *game);
void					print_error(char *error, int print);

// -------- Player & Hook --------
int						key_press_hook(int key, t_game *game);
int						key_release_hook(int key, t_player *player);
void					player_movement(t_player *player);
int						run_game(t_game *game);

// ---------- Parsing ------------
void					rmv_final_whitespace(char *str);
bool					parse_map(char *filename, t_game *game, int nb_line);
bool					create_map(t_game *game, int fd, char *line);
bool					find_color(char *str, t_game *game, char texture);
bool					init_all(t_game *game);
int						next_whitespace(char *line, int i);
bool					parse_file(char *filename, t_game *game);
bool					parse_texture(int fd, t_game *game, int *nb_line, \
										char **rest);
t_intvector				get_map_size(int fd, char *line, bool *error);
bool					find_player(t_game *game);
int						skip_whitespace(char *str);
bool					check_map(t_game *game);
void					get_data_address(t_image *image, t_intvector size);

// ---------- Raycasting ---------
void					raycasting(t_game *game);
enum e_orientation		get_wall_orientation(t_player player, t_vector wall);
void					draw_vertical(t_game *game, int x, t_vector wall, \
										double dist);
t_vector				get_wall_hit(t_vector fpos, char **map, float angle, \
										t_intvector map_size);
t_vector				get_wall_hit_se(t_vector fpos, char **map, float angle, \
										t_intvector map_size);
t_vector				get_wall_hit_ne(t_vector fpos, char **map, float angle, \
										t_intvector map_size);
t_vector				get_wall_hit_sw(t_vector fpos, char **map, float angle, \
										t_intvector map_size);
t_vector				get_wall_hit_nw(t_vector fpos, char **map, float angle);

#endif

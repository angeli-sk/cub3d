/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 16:40:24 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 22:06:10 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define LINUX 0
# define APPLE 0
# ifdef __linux__
# undef LINUX
# define LINUX 1
# else
# undef APPLE
# define APPLE 1
# endif

# include <stdlib.h>

typedef enum	e_rror
{
	invalid_map = -1,
	invalid_char = -2,
	invalid_F = -3,
	invalid_C = -4,
	too_many_nums = -18,
	up = 0,
	left = 1,
	right = 2,
	down = 3,
	turn_r = 4,
	turn_l = 5
}				t_rror;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	int				x;
	int				y;
	int				xmax;
	int				ymax;
	int				img_width;
	int				img_height;
	double			cam_x;
	double 			ray_x;
	double			ray_y;
	int				w;
	int				h;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int 			map_x;
	int 			map_y;
	double 			side_d_x;
	double 			side_d_y;
	double 			delta_d_x;
	double 			delta_d_y;
	double			perp_w_d;
	int 			line_h;
	int 			draw_start;
	int 			draw_end;
	int 			step_x;
	int 			step_y;
	int 			hit;
	int 			side;
	int 			colorwall;
	int 			key;
	double			spd;
	double 			rot_speed;
	double 			olddir_x;
	double 			oldplane_x;
	int				walksies[6];
	double 			wall_x;
	double 			tex_x;
	double 			tex_y;
	double			step;
	double 			tex_pos;
	double 			*z_buff;
}					t_vars;

typedef struct		s_sprite
{
	double 			spr_x;
	double 			spr_y;
	double 			inv_det;
	double 			trans_x;
	double 			trans_y;
	int 			spr_screen_y;
	int 			spr_h;
	int 			spr_w;
	int 			draw_start_y;
	int				draw_start_x;
	int 			draw_end_y;
	int 			draw_end_x;
	int 			stripe;
	int 			d;
}					t_sprite;

typedef struct		s_array
{
	int 			x;
	int 			y;
	void 			*img;
	char 			*addr;
	double 			distance;
	int				bits_per_pixel;
	int 			line_length;
	int 			endian;
}					t_array;

typedef struct		s_parse
{
	int				rx;
	int				ry;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				fr;
	int				fg;
	int				fb;
	int				cr;
	int				cg;
	int				cb;
	unsigned int	f_color;
	unsigned int	c_color;
	char			*temp;
	char			**map;
	char			**mapcopy;
	int				beginmap;
	int				error;
	int				maxstrlen;
	int				i;
	int				maxrx;
	int				maxry;
	int				players;
	int				objects;
	int				startx;
	int				starty;
	int				max_y;
	char			*line;
	int				f;
	int				c;
	int				r;
	int 			fd;
	int				ret;
	char			*free_temp;
	char			*num_temp;
	int				num_st;
	int				num_check;
	int				num_i;
	char			num_ltr;
	int				num_error;
	char			ltr;
	int				save;
	int 			loop;
	t_data			img;
	t_vars			vars;
	t_array 		*arr;
	t_sprite 		sprite;
	int				*sprite_order;
	t_array 		tex[5];
}					t_parse;

typedef struct		s_splitty
{
	int				y;
	int				len;
	char			c;
	int				maxlen;
}					t_splitty;

typedef struct		s_struct_num
{
	int				st;
	int				check;
	char			*temp;
	int				i;
	char			ltr;
	int				error;
}					t_struct_num;

typedef struct		s_mapinfo
{
	char 			wall;
	char 			item;
	char 			emptyspace;
	char 			player;
}					t_mapinfo;

typedef struct		s_move
{
	int 			y_up;
	int 			y_down;
	int 			y_left;
	int 			y_right;
	int 			x_up;
	int 			x_down;
	int 			x_left;
	int 			x_right;
}					t_move;

/*libft*/
char			*ft_strjoin_c3d(t_parse *cub, char const *s1, char const *s2);
char			**ft_split_c3d(t_parse *cub, char const *s, char c);
void			*ft_calloc_mlx(size_t count, size_t size);
void			ft_bzero_mlx(void *s, size_t n);

//main
void			cub3d(int argc, char **argv);

/*parse_cub3d*/
int				ft_checkmapplacement(t_parse *cub);
void			parser(t_parse *cub, char **argv, int argc);

/*cub_num_parse*/
void 			num_check_p2(t_parse *cub);
void			ft_check_if_numcorrect(t_parse *cub);
void			num_check(t_parse *cub);
void			struct_num(t_parse *cub, int *adr1, int *adr2, int *adr3);

/*cub_parse*/
void			check_if_s_empty(t_parse *cub);
char			*struct_path(t_parse *cub);

/*cub_parse_exit*/
void			freemaps(t_parse *cub);
void			freevars(t_parse *cub);
void			ft_exit_c3d(t_parse *cub, char *s, int len);

/*cub_parse_init*/
void			struct_init(t_parse *cub);
void			get_tex(t_parse *cub);
void			mlx_vars_init(t_parse *cub);

/*cub_parse_map*/
void			check_if_empty_start(t_parse *cub);
void			playerobjcheck(t_parse *cub);
void			validity(t_parse *cub);

/*cub_mlx*/
int				render_next_frame(t_parse *cub);
int 			draw(t_vars *vars);
void			mlx(t_parse *cub, char **argv, int argc);
void			mlx_calc(t_parse *cub);

void			bitmap(t_parse *cub);
int				bitmap_header(t_parse *cub, int fd, int padding);

//sprite
void			mlx_sprite(t_parse *cub);

//walksies
void			walksies(t_parse *cub, t_move *move);

//cal
void			mlx_calc(t_parse *cub);

//mlx_utility
void			ft_sort(t_parse *cub);
int				ft_checkposition(t_parse *cub, int x, int y);
int				destroy(t_parse *cub);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

//verline
void			ft_verLine(int draw_start, int draw_end, t_parse *cub);

//keys
int				key_released(int keycode, t_parse *cub);
int				key_pressed(int keycode, t_parse *cub);
void			ft_verline(int draw_start, int draw_end, t_parse *cub);

void			file_checkor(t_parse *cub);
#endif

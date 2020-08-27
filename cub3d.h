/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 16:40:24 by akramp        #+#    #+#                 */
/*   Updated: 2020/08/19 14:30:36 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <stdio.h>

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


typedef struct	s_data 
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	int			x;
	int			y;
	int			xmax;
	int			ymax;
	int     img_width;
	int     img_height;
    //--------------------
    double cameraX; //x-coordinate in camera space
    double rayDirX;
    double rayDirY;
    int w;
    int h;
    double posX;
    double posY; //x and y start position
    double dirX;
    double dirY; //initial direction vector ;fix that with s e w etc.
    double planeX;
    double planeY; //the 2d raycaster version of camera plane
    int mapX;//which box of the map we're in
    int mapY;
    double sideDistX;//length of ray from current position to next x or y-side
    double sideDistY;
    double deltaDistX;//length of ray from one x or y-side to next x or y-side
    double deltaDistY;
    double perpWallDist;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int stepX;//what direction to step in x or y-direction (either +1 or -1)
    int stepY;
	int hit; //was there a wall hit?
    int side; //was a NS or a EW wall hit?
	int colorwall;
	int key;
	double moveSpeed;
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;
	int	walksies[6];
	double wallX;
	double texX;
	double texY;
	double step;
	double texPos;
}				t_vars;

typedef struct s_array
{
	int x;
	int y;
	void *img; //img die mlx return van de sprite
	char *addr;
	double distance;
	int bits_per_pixel;
	int line_length;
	int endian;
}				t_array;

typedef struct	s_parse
{
	int		rx;
	int		ry;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
	char	*temp;
	char	**map;
	char	**mapcopy;
	int		beginmap;
	int		error;
	int		maxstrlen;
	int		i;
	int		maxrx;
	int		maxry;
	int		players;
	int		objects;
	int		startx;
	int		starty;
	int		max_y;
	char	*line;
	int		f;
	int		c;
	int		r;
	int 	fd;
	int		ret;
	char	*free_temp;
	char	*num_temp;
	int		num_st;
	int		num_check;
	int		num_i;
	char	num_ltr;
	int		num_error;
	char	ltr;
	t_data	img;
	t_vars vars;
	t_array *arr;
	t_array tex[5];
}				t_parse;

typedef struct s_splitty
{
	int		y;
	int		len;
	char	c;
	int		maxlen;
}				t_splitty;

typedef struct	s_struct_num
{
	int		st;
	int		check;
	char	*temp;
	int		i;
	char	ltr;
	int		error;
}				t_struct_num;

typedef struct	s_mapinfo
{
	char wall;
	char item;
	char emptyspace;
	char player;
}				t_mapinfo;



/*libft*/
char	*ft_strjoin_c3d(t_parse *cub, char const *s1, char const *s2);
char		**ft_split_c3d(t_parse *cub, char const *s, char c);
void	*ft_calloc_mlx(size_t count, size_t size);
void	ft_bzero_mlx(void *s, size_t n);

/*parse_cub3d*/
void		read_map(t_parse *cub);
int	ft_checkmapplacement(t_parse *cub);
void		parsing(t_parse *cub);
void	readfile(t_parse *cub, char *path);
void	parser(t_parse *cub, char **argv, int argc);
void	cub3d(int argc, char **argv);

/*cub_num_parse*/
void num_check_p2(t_parse *cub);
void	ft_check_if_numcorrect(t_parse *cub);
void	num_check(t_parse *cub);
void	struct_num(t_parse *cub, int *adr1, int *adr2, int *adr3);

/*cub_parse*/
void		check_if_s_empty(t_parse *cub);
char	*struct_path(t_parse *cub);

/*cub_parse_exit*/
void	freemaps(t_parse *cub);
void	freevars(t_parse *cub);
void	ft_write_error(char *s, int len);
void	ft_exit_c3d(t_parse *cub, char *s, int len);

/*cub_parse_init*/
void	struct_num_init(t_parse *cub);
void	struct_init(t_parse *cub);

/*cub_parse_map*/
void	check_if_empty_start(t_parse *cub);
void	playerobjcheck(t_parse *cub);
void	ft_floodfill(t_parse *cub, int y, int x);
void	mapvalidity(t_parse *cub);
void	validity(t_parse *cub);

/*cub_mlx*/
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		keys(int keycode, t_parse *cub);
int	render_next_frame(t_parse *cub);
int draw(t_vars *vars);
void	ft_mlx(t_parse *cub, char **argv, int argc);
void	mlx_calc(t_parse *cub);

#endif
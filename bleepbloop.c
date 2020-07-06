/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bleepbloop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:24:05 by akramp        #+#    #+#                 */
/*   Updated: 2020/06/25 17:00:17 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

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
}				t_vars;

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr_fd(-2, fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		keys(int keycode, t_vars *vars)
{
	ft_putnbr_fd(keycode, 1);
	write(1, "\n", 1);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	return (0);
}

int	render_next_frame()	
{
	return (0);
}

int draw(t_vars *vars)
{
	int     img_width;
    int		img_height;

	img_width = 1920;
	img_height = 1080;
	t_data img;
	img.img = mlx_new_image(vars->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								&img.line_length,&img.endian);
	img.img = mlx_xpm_file_to_image(vars->mlx, "./dogo.xpm", &img_width, &img_height);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (1);
}

int		main(void)
{
	t_data	img;
	t_vars	vars;
	int     img_width;
	int     img_height;
	// double posX = 22, posY = 12;  //x and y start position
  	// double dirX = -1, dirY = 0; //initial direction vector
  	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

  	// double time = 0; //time of current frame
  	// double oldTime = 0; //time of previous frame


	img_width = 1280;
	img_height = 1024;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "🄲🅄🄱3🄳");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								&img.line_length,&img.endian);
	vars.y = 0;
	vars.x = 0;
	write(1, "lol\n", 4);
	while (vars.y < 1080)
	{
		vars.x = 0;
		while (vars.x < 1920)
		{
			my_mlx_pixel_put(&img, vars.x, vars.y, 0x27273a);
			vars.x++;
		}
		vars.y++;
	}

	vars.y = 400;
	vars.xmax = 900;
	vars.ymax = 600;
	//mlx_loop_hook(vars.mlx, render_next_frame(), vars);

	while (vars.y < vars.ymax)
	{
		vars.x = 800;
		while (vars.x < vars.xmax)
		{
			my_mlx_pixel_put(&img, vars.x, vars.y, 0xe34f8c);
			vars.x++;
		}
		vars.ymax--;
		vars.xmax--;
		vars.y++;
	}

	mlx_loop_hook(vars.mlx, draw, &vars.mlx);
	mlx_loop(vars.mlx);
}

//purple 0xc7adfb
//orange 0xf8c275
//dark purple  0x27273a
//green 0x97f36d
//pink	0xe34f8c
//lightpink 0xf6cff7
//lightpurps 0x6d5073

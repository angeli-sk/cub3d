/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 14:24:05 by akramp        #+#    #+#                 */
/*   Updated: 2020/05/08 16:24:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
	int		xmax;
	int 	ymax;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								&img.line_length,&img.endian);
	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			my_mlx_pixel_put(&img, x, y, 0x27273a);
			x++;
		}
		y++;
	}
	y = 200;
	while (y < 700)
	{
		x = 500;
		while (x < 1000)
		{
			my_mlx_pixel_put(&img, x, y, 0xf8c275);
			x++;
		}
		y++;
	}
	y = 400;
	while (y < 600)
	{
		x = 800;
		while (x < 1000)
		{
			my_mlx_pixel_put(&img, x, y, 0xc7adfb);
			x++;
		}
		y++;
	}
	y = 300;
	xmax = 1000;
	while (y < 600)
	{
		x = 500;
		while (x < xmax)
		{
			my_mlx_pixel_put(&img, x, y, 0x97f36d);
			x++;
		}
		if(xmax > 0)
			xmax--;
		y++;
	}
	y = 400;
	xmax = 900;
	ymax = 600;
	while (y < ymax)
	{
		x = 800;
		while (x < xmax)
		{
			my_mlx_pixel_put(&img, x, y, 0xe34f8c);
			x++;
		}
		ymax--;
		xmax--;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

//purple 0xc7adfb
//orange 0xf8c275
//dark purple  0x27273a
//green 0x97f36d
//pink	0xe34f8c
//lightpink 0xf6cff7
//lightpurps 0x6d5073

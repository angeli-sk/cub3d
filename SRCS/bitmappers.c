/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmappers.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:37:45 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 22:42:12 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>

void	bitmap_init(t_parse *cub)
{
	cub->img.img = mlx_new_image(cub->vars.mlx, cub->rx, cub->ry);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length, &cub->img.endian);
	mlx_calc(cub);
	mlx_sprite(cub);
	mlx_new_window(cub->vars.mlx, cub->rx, cub->ry, "🄲🅄🄱3🄳");
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	mlx_loop(cub->vars.mlx);
}

int		bitmap_header(t_parse *cub, int fd, int padding)
{
	char	header[54];

	ft_bzero(header, 54);
	fd = open("screenshot.bmp", O_RDWR | O_CREAT, 0777);
	header[0] = 'B';
	header[1] = 'M';
	padding = 4 - ((cub->rx * 3) % 4);
	if (padding == 4)
		padding = 0;
	header[2] = ((cub->rx * (cub->ry + padding) * 3) + 54);
	header[6] = 0;
	header[10] = 54;
	header[14] = 40;
	ft_memcpy(header + 18, &cub->rx, 4);
	ft_memcpy(header + 22, &cub->ry, 4);
	header[26] = 1;
	header[28] = 24;
	return (padding);
}

void	bitmap(t_parse *cub)
{
	int		fd;
	int		padding;
	char	*color;
	int		y;
	int		x;

	y = cub->ry - 1;
	x = 0;
	bitmap_init(cub);
	padding = bitmap_header(cub, fd, padding);
	while (y >= 0)
	{printf("rx=%d && ry=%d\n", cub->rx, cub->ry);
		x = 0;
		while (x < cub->rx)
		{
			color = (cub->img.addr + ((cub->img.line_length * y) \
			+ (x * (cub->img.bits_per_pixel / 8))));
			write(fd, color, 3);
			//printf("color=[%u]\n", color);
			x++;
		}
		write(fd, "/0/0/0", padding);
		y--;
	}
	close(fd);
	exit(0);
}

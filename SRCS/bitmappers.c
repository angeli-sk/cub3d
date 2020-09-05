/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmappers.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:37:45 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 12:54:59 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>
#include <fcntl.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>

static int	header_bm(t_parse *cub, int padding)
{
	char header[54];

	ft_bzero(header, 54);
	cub->img.img = mlx_new_image(cub->vars.mlx, cub->rx, cub->ry);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length, &cub->img.endian);
	mlx_calc(cub);
	mlx_sprite(cub);
	cub->fd = open("screenshot.bmp", O_RDWR | O_CREAT, 0777);
	header[0] = 'B';
	header[1] = 'M';
	padding = 4 - (cub->rx * 3) % 4;
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
	write(cub->fd, header, 54);
	return (padding);
}

void		bitmap(t_parse *cub)
{
	int		padding;
	char	*color;
	int		y;
	int		x;

	y = cub->ry;
	x = 0;
	padding = header_bm(cub, padding);
	while (y >= 0)
	{
		x = 0;
		while (x < cub->rx)
		{
			color = (cub->img.addr + ((cub->img.line_length * y)
				+ (x * (cub->img.bits_per_pixel / 8))));
			write(cub->fd, color, 3);
			x++;
		}
		write(cub->fd, "/0/0/0", padding);
		y--;
	}
	close(cub->fd);
	exit(0);
}

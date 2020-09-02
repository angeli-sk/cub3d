/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:34:52 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 21:35:28 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <mlx.h>

void	get_tex(t_parse *cub)
{
	cub->tex[0].img = mlx_png_file_to_image(cub->vars.mlx, \
	cub->no, &cub->tex[0].x, &cub->tex[0].y);
	cub->tex[0].addr = mlx_get_data_addr(cub->tex[0].img, \
	&cub->tex[0].bits_per_pixel, &cub->tex[0].line_length, &cub->tex[0].endian);
	cub->tex[1].img = mlx_png_file_to_image(cub->vars.mlx, \
	cub->so, &cub->tex[1].x, &cub->tex[1].y);
	cub->tex[1].addr = mlx_get_data_addr(cub->tex[1].img, \
	&cub->tex[1].bits_per_pixel, &cub->tex[1].line_length, &cub->tex[1].endian);
	cub->tex[2].img = mlx_png_file_to_image(cub->vars.mlx, \
	cub->we, &cub->tex[2].x, &cub->tex[2].y);
	cub->tex[2].addr = mlx_get_data_addr(cub->tex[2].img, \
	&cub->tex[2].bits_per_pixel, &cub->tex[2].line_length, &cub->tex[2].endian);
	cub->tex[3].img = mlx_png_file_to_image(cub->vars.mlx, \
	cub->ea, &cub->tex[3].x, &cub->tex[3].y);
	cub->tex[3].addr = mlx_get_data_addr(cub->tex[3].img, \
	&cub->tex[3].bits_per_pixel, &cub->tex[3].line_length, &cub->tex[3].endian);
	cub->tex[4].img = mlx_png_file_to_image(cub->vars.mlx, \
	cub->s, &cub->tex[4].x, &cub->tex[4].y);
	cub->tex[4].addr = mlx_get_data_addr(cub->tex[4].img, \
	&cub->tex[4].bits_per_pixel, &cub->tex[4].line_length, &cub->tex[4].endian);
}

void	struct_bzero(t_parse *cub)
{
	int i;

	ft_bzero(cub, sizeof(t_parse));
	ft_bzero(&cub->img, sizeof(t_parse));
	ft_bzero(&cub->vars, sizeof(t_parse));
	ft_bzero(&cub->arr, sizeof(t_parse));
	ft_bzero(&cub->sprite, sizeof(t_jonas));
	i = 0;
	while (i < 6)
	{
		ft_bzero(&cub->vars.walksies[i], sizeof(t_array));
		i++;
	}
	i = 0;
	while (i < 5)
	{
		ft_bzero(&cub->tex[i], sizeof(t_parse));
		i++;
	}
}

void	view_init(t_parse *cub)
{
	if (cub->ltr == 'S')
	{
		cub->vars.dirY = 1.0;
		cub->vars.planeX = -0.66;
	}
	if (cub->ltr == 'W')
	{
		cub->vars.dirX = -1.0;
		cub->vars.planeY = -0.66;
	}
	if (cub->ltr == 'N')
	{
		cub->vars.dirY = -1.0;
		cub->vars.planeX = 0.66;
	}
	if (cub->ltr == 'E')
	{
		cub->vars.dirX = 1.0;
		cub->vars.planeY = 0.66;
	}
}

void	mlx_vars_init(t_parse *cub)
{
	cub->vars.speedy = 0.1;
	cub->vars.rotSpeed = 0.05;
	cub->vars.oldDirX = 0;
	cub->vars.oldPlaneX = 0;
	cub->vars.colorwall = 255;
	cub->vars.cameraX = 0.0;
	cub->vars.rayDirX = 0.0;
	cub->vars.rayDirY = 0.0;
	cub->vars.x = 0;
	cub->vars.h = cub->ry;
	cub->vars.w = cub->rx;
	cub->vars.posX = (double)cub->startx + 0.5;
	cub->vars.posY = (double)cub->starty + 0.5;
	cub->vars.ZBuffer = malloc(sizeof(double) * cub->rx);
	if (cub->vars.ZBuffer == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	cub->spriteOrder = malloc(sizeof(int) * cub->objects);
	view_init(cub);
}

void	struct_init(t_parse *cub)
{
	struct_bzero(cub);
	mlx_vars_init(cub);
	cub->rx = -1;
	cub->ry = -1;
	cub->fr = -1;
	cub->fr = -1;
	cub->fb = -1;
	cub->cr = -1;
	cub->cg = -1;
	cub->cb = -1;
	cub->i = -1;
	cub->maxstrlen = -1;
	mlx_get_screen_size(cub->vars.mlx, &cub->maxrx, &cub->maxry);
	cub->num_check = 1;
}

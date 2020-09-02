/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:18:31 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 22:21:48 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		calc_tex(t_parse *cub)
{
	int tex;

	tex = 0;
	if (cub->vars.side == 1 && cub->vars.rayDirY > 0)
		tex = 0;
	if (cub->vars.side == 1 && cub->vars.rayDirY < 0)
		tex = 1;
	if (cub->vars.side == 0 && cub->vars.rayDirX > 0)
		tex = 2;
	if (cub->vars.side == 0 && cub->vars.rayDirX < 0)
		tex = 3;
	return (tex);
}

static void	calc_drawstart(t_parse *cub, int drawStart, int tex)
{
	while (cub->vars.y < drawStart)
	{
		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x27273a);
		cub->vars.y++;
	}
	if (cub->vars.side == 0)
		cub->vars.wallX = cub->vars.posY + cub->vars.perpWallDist
		* cub->vars.rayDirY;
	else
		cub->vars.wallX = cub->vars.posX + cub->vars.perpWallDist
		* cub->vars.rayDirX;
	cub->vars.wallX -= floor((cub->vars.wallX));
	cub->vars.texX = (int)(cub->vars.wallX * (double)(cub->tex[tex].x));
	if (cub->vars.side == 0 && cub->vars.rayDirX > 0)
		cub->vars.texX = cub->tex[tex].x - cub->vars.texX - 1;
	if (cub->vars.side == 1 && cub->vars.rayDirY < 0)
		cub->vars.texX = cub->tex[tex].x - cub->vars.texX - 1;
	cub->vars.step = 1.0 * cub->tex[tex].y / cub->vars.lineHeight;
	cub->vars.texPos = (cub->vars.drawStart - cub->vars.h / 2 +
		cub->vars.lineHeight / 2) * cub->vars.step;
	cub->vars.y = drawStart;
	cub->vars.texX = cub->tex[tex].x - cub->vars.texX - 1;
}

static void	calc_end(t_parse *cub)
{
	while (cub->vars.y < cub->ry)
	{
		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, 0x97f36d);
		cub->vars.y++;
	}
}

void		ft_verLine(int drawStart, int drawEnd, t_parse *cub)
{
	int				tex;
	char			*test;
	unsigned int	color;

	cub->vars.y = 0;
	tex = calc_tex(cub);
	calc_drawstart(cub, drawStart, tex);
	while (cub->vars.y < drawEnd)
	{
		cub->vars.texY = (int)cub->vars.texPos & (cub->tex[tex].y - 1);
		cub->vars.texPos += cub->vars.step;
		if (cub->vars.texY >= 0 && cub->vars.texX >= 0)
			color = *(unsigned int *)(cub->tex[tex].addr +
			((cub->tex[tex].line_length * (int)cub->vars.texY) +
			(int)cub->vars.texX * (cub->tex[tex].bits_per_pixel / 8)));
		else
			color = 0;
		if (color < 0)
			color = 0;
		my_mlx_pixel_put(&cub->img, cub->vars.x, cub->vars.y, color);
		cub->vars.y++;
	}
	calc_end(cub);
}

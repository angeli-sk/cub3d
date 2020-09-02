/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:52:19 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 22:04:17 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_value(t_parse *cub)
{
	cub->vars.colorwall = 13086203;
	cub->vars.cameraX = 2 * cub->vars.x / (double)cub->vars.w - 1;
	cub->vars.rayDirX = cub->vars.dirX + cub->vars.planeX * cub->vars.cameraX;
	cub->vars.rayDirY = cub->vars.dirY + cub->vars.planeY * cub->vars.cameraX;
	cub->vars.mapX = (int)cub->vars.posX;
	cub->vars.mapY = (int)cub->vars.posY;
	if (cub->vars.rayDirY == 0)
		cub->vars.deltaDistX = 0;
	else if (cub->vars.rayDirX == 0)
		cub->vars.deltaDistX = 1;
	else
		cub->vars.deltaDistX = fabs(1 / cub->vars.rayDirX);
	if (cub->vars.rayDirX == 0)
		cub->vars.deltaDistY = 0;
	else if (cub->vars.rayDirY == 0)
		cub->vars.deltaDistY = 1;
	else
		cub->vars.deltaDistY = fabs(1 / cub->vars.rayDirY);
}

static void	calc_sidedist(t_parse *cub)
{
	if (cub->vars.rayDirX < 0)
	{
		cub->vars.stepX = -1;
		cub->vars.sideDistX =
			(cub->vars.posX - cub->vars.mapX) * cub->vars.deltaDistX;
	}
	else
	{
		cub->vars.stepX = 1;
		cub->vars.sideDistX =
			(cub->vars.mapX + 1.0 - cub->vars.posX) * cub->vars.deltaDistX;
	}
	if (cub->vars.rayDirY < 0)
	{
		cub->vars.stepY = -1;
		cub->vars.sideDistY =
			(cub->vars.posY - cub->vars.mapY) * cub->vars.deltaDistY;
	}
	else
	{
		cub->vars.stepY = 1;
		cub->vars.sideDistY =
			(cub->vars.mapY + 1.0 - cub->vars.posY) * cub->vars.deltaDistY;
	}
}

static void	calc_hit(t_parse *cub)
{
	cub->vars.hit = 0;
	while (cub->vars.hit == 0)
	{
		if (cub->vars.sideDistX < cub->vars.sideDistY)
		{
			cub->vars.sideDistX += cub->vars.deltaDistX;
			cub->vars.mapX += cub->vars.stepX;
			cub->vars.side = 0;
		}
		else
		{
			cub->vars.sideDistY += cub->vars.deltaDistY;
			cub->vars.mapY += cub->vars.stepY;
			cub->vars.side = 1;
		}
		if (cub->map[cub->vars.mapY][cub->vars.mapX] == '1')
			cub->vars.hit = 1;
	}
}

void		mlx_calc(t_parse *cub)
{
	cub->vars.x = 0;
	while (cub->vars.x < cub->vars.w)
	{
		calc_value(cub);
		calc_sidedist(cub);
		calc_hit(cub);
		if (cub->vars.side == 0)
			cub->vars.perpWallDist = (cub->vars.mapX - cub->vars.posX +
			(1 - cub->vars.stepX) / 2) / cub->vars.rayDirX;
		else
			cub->vars.perpWallDist = (cub->vars.mapY - cub->vars.posY +
				(1 - cub->vars.stepY) / 2) / cub->vars.rayDirY;
		cub->vars.lineHeight = (int)(cub->vars.h / cub->vars.perpWallDist);
		cub->vars.drawStart = (-cub->vars.lineHeight / 2) + (cub->vars.h / 2);
		if (cub->vars.drawStart < 0)
			cub->vars.drawStart = 0;
		cub->vars.drawEnd = (cub->vars.lineHeight / 2) + (cub->vars.h / 2);
		if (cub->vars.drawEnd >= cub->vars.h)
			cub->vars.drawEnd = cub->vars.h - 1;
		if (cub->vars.side == 1)
			cub->vars.colorwall = cub->vars.colorwall / 2;
		ft_verLine(cub->vars.drawStart, cub->vars.drawEnd, cub);
		cub->vars.ZBuffer[cub->vars.x] = cub->vars.perpWallDist;
		cub->vars.x++;
	}
}

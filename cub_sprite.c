/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_sprite.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:13:08 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 21:20:23 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sprite_startend(t_parse *cub)
{
	cub->sprite.drawStartY = -cub->sprite.spriteHeight / 2 + cub->ry / 2;
	if (cub->sprite.drawStartY < 0)
		cub->sprite.drawStartY = 0;
	cub->sprite.drawEndY = cub->sprite.spriteHeight / 2 + cub->ry / 2;
	if (cub->sprite.drawEndY >= cub->ry)
		cub->sprite.drawEndY = cub->ry;
	cub->sprite.spriteWidth = abs((int)(cub->ry / (cub->sprite.transformY)));
	cub->sprite.drawStartX = -(cub->sprite.spriteWidth) / 2
		+ cub->sprite.spriteScreenX;
	if (cub->sprite.drawStartX < 0)
		cub->sprite.drawStartX = 0;
	cub->sprite.drawEndX = cub->sprite.spriteWidth / 2
		+ cub->sprite.spriteScreenX;
	if (cub->sprite.drawEndX >= cub->rx)
		cub->sprite.drawEndX = cub->rx;
	cub->sprite.stripe = cub->sprite.drawStartX;
}

static void	calc_sprite(t_parse *cub, int i)
{
	cub->sprite.spriteX = cub->arr[cub->spriteOrder[i]].x - cub->vars.posX;
	cub->sprite.spriteY = cub->arr[cub->spriteOrder[i]].y - cub->vars.posY;
	cub->sprite.spriteX += 0.5;
	cub->sprite.spriteY += 0.5;
	cub->sprite.invDet = 1.0 / (cub->vars.planeX *
		cub->vars.dirY - cub->vars.dirX * cub->vars.planeY);
	cub->sprite.transformX = cub->sprite.invDet * (cub->vars.dirY *
		cub->sprite.spriteX - cub->vars.dirX * cub->sprite.spriteY);
	cub->sprite.transformY = cub->sprite.invDet * (-cub->vars.planeY *
		cub->sprite.spriteX + cub->vars.planeX * cub->sprite.spriteY);
	cub->sprite.spriteScreenX = (int)((cub->rx / 2) *
		(1 + cub->sprite.transformX / cub->sprite.transformY));
	cub->sprite.spriteHeight = abs((int)(cub->ry / (cub->sprite.transformY)));
	sprite_startend(cub);
}

static void	draw_sprite_line(t_parse *cub)
{
	unsigned int color;

	color = 0;
	cub->vars.texX = (int)(256 * (cub->sprite.stripe -
		(-cub->sprite.spriteWidth / 2 + cub->sprite.spriteScreenX))
		* cub->tex[4].x / cub->sprite.spriteWidth) / 256;
	cub->sprite.d = (cub->vars.y) * 256 - cub->ry * 128
		+ cub->sprite.spriteHeight * 128;
	cub->vars.texY = ((cub->sprite.d * cub->tex[4].x)
		/ cub->sprite.spriteHeight) / 256;
	color = *(unsigned int *)(cub->tex[4].addr
		+ (cub->tex[4].line_length * (int)cub->vars.texY
		+ (int)cub->vars.texX * (cub->tex[4].bits_per_pixel / 8)));
	if (color > 0)
		my_mlx_pixel_put(&cub->img,
			cub->sprite.stripe, cub->vars.y, color);
}

static void	draw_sprite(t_parse *cub)
{
	while (cub->sprite.stripe < cub->sprite.drawEndX)
	{
		cub->vars.texX = (int)(256 * (cub->sprite.stripe -
			(-cub->sprite.spriteWidth / 2 + cub->sprite.spriteScreenX))
			* cub->tex[4].x / cub->sprite.spriteWidth) / 256;
		if (cub->sprite.transformY > 0 && cub->sprite.stripe >= 0 &&
				cub->sprite.stripe < cub->vars.w && cub->sprite.transformY <
				cub->vars.ZBuffer[cub->sprite.stripe])
			cub->vars.y = cub->sprite.drawStartY;
		while (cub->vars.y < cub->sprite.drawEndY && cub->sprite.stripe >= 0
			&& cub->sprite.stripe < cub->rx)
		{
			draw_sprite_line(cub);
			cub->vars.y++;
		}
		cub->sprite.stripe++;
	}
}

void		mlx_sprite(t_parse *cub)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (i < cub->objects)
	{
		cub->spriteOrder[i] = i;
		cub->arr[cub->spriteOrder[i]].distance = ((cub->vars.posX
			- cub->arr[cub->spriteOrder[i]].x) * (cub->vars.posX
			- cub->arr[cub->spriteOrder[i]].x) + (cub->vars.posY
			- cub->arr[cub->spriteOrder[i]].y) * (cub->vars.posY
			- cub->arr[cub->spriteOrder[i]].y));
		i++;
	}
	ft_sort(cub);
	i = 0;
	while (i < cub->objects)
	{
		calc_sprite(cub, i);
		draw_sprite(cub);
		i++;
	}
}

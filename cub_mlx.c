/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_mlx.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:10:05 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 22:30:24 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_render_next_frame(t_parse *cub, t_boris *move)
{
	move->x_up = (int)(cub->vars.posX + (cub->vars.dirX * cub->vars.speedy));
	move->y_up = (int)(cub->vars.posY + (cub->vars.dirY * cub->vars.speedy));
	move->x_down = (int)(cub->vars.posX - (cub->vars.dirX * cub->vars.speedy));
	move->y_down = (int)(cub->vars.posY - (cub->vars.dirY * cub->vars.speedy));
	move->x_left = (int)(cub->vars.posX - (cub->vars.dirY * cub->vars.speedy));
	move->y_left = (int)(cub->vars.posY + (cub->vars.dirX * cub->vars.speedy));
	move->x_right = (int)(cub->vars.posX + (cub->vars.dirY * cub->vars.speedy));
	move->y_right = (int)(cub->vars.posY - (cub->vars.dirX * cub->vars.speedy));
}

int	render_next_frame(t_parse *cub)
{
	t_boris move;

	if (cub->vars.walksies[up] == 0 && cub->vars.walksies[left] == 0 &&
		cub->vars.walksies[down] == 0 && cub->vars.walksies[right] == 0 &&
		cub->vars.walksies[turn_l] == 0 && cub->vars.walksies[turn_r] == 0 &&
		cub->loop == 1)
		return (1);
	cub->img.img = mlx_new_image(cub->vars.mlx, cub->rx, cub->ry);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
								&cub->img.line_length,&cub->img.endian);
	init_render_next_frame(cub, &move);
	walksies(cub, &move);
	mlx_calc(cub);
	mlx_sprite(cub);
	mlx_put_image_to_window(cub->vars.mlx, cub->vars.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->vars.mlx, cub->img.img);
	cub->loop = 1;
	return (1);
}

void	mlx(t_parse *cub, char **argv, int argc)
{
	mlx_vars_init(cub);
	cub->vars.mlx = mlx_init();
	if (cub->save == 0)
	{
		cub->vars.win =
		mlx_new_window(cub->vars.mlx, cub->rx, cub->ry, "🄲🅄🄱3🄳");
	}
	get_tex(cub);
	if (cub->save == 1)
		bitmap(cub);
	mlx_hook(cub->vars.win, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->vars.win, 3, 2L << 0, key_released, cub);
	mlx_hook(cub->vars.win, 17, 1L << 17, destroy, cub);
	mlx_loop_hook(cub->vars.mlx, render_next_frame, cub);
	mlx_loop(cub->vars.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:23:35 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:11 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		key_pressed(int keycode, t_parse *cub)
{
	if ((keycode == 65307 && LINUX == 1) || (keycode == 53 && APPLE == 1))
		destroy(cub);
	if ((keycode == 13 && APPLE == 1) || (keycode == 119 && LINUX == 1))
		cub->vars.walksies[up] = 1;
	if ((keycode == 1 && APPLE == 1) || (keycode == 115 && LINUX == 1))
		cub->vars.walksies[down] = 1;
	if ((keycode == 123 && APPLE == 1) || (keycode == 65361 && LINUX == 1))
		cub->vars.walksies[turn_l] = 1;
	if ((keycode == 124 && APPLE == 1) || (keycode == 65363 && LINUX == 1))
		cub->vars.walksies[turn_r] = 1;
	if ((keycode == 2 && APPLE == 1) || (keycode == 100 && LINUX == 1))
		cub->vars.walksies[right] = 1;
	if ((keycode == 0 && APPLE == 1) || (keycode == 97 && LINUX == 1))
		cub->vars.walksies[left] = 1;
	return (0);
}

int		key_released(int keycode, t_parse *cub)
{
	if ((keycode == 65307 && LINUX == 1) || (keycode == 53 && APPLE == 1))
		destroy(cub);
	if ((keycode == 13 && APPLE == 1) || (keycode == 119 && LINUX == 1))
		cub->vars.walksies[up] = 0;
	if ((keycode == 1 && APPLE == 1) || (keycode == 115 && LINUX == 1))
		cub->vars.walksies[down] = 0;
	if ((keycode == 123 && APPLE == 1) || (keycode == 65361 && LINUX == 1))
		cub->vars.walksies[turn_l] = 0;
	if ((keycode == 124 && APPLE == 1) || (keycode == 65363 && LINUX == 1))
		cub->vars.walksies[turn_r] = 0;
	if ((keycode == 2 && APPLE == 1) || (keycode == 100 && LINUX == 1))
		cub->vars.walksies[right] = 0;
	if ((keycode == 0 && APPLE == 1) || (keycode == 97 && LINUX == 1))
		cub->vars.walksies[left] = 0;
	return (0);
}

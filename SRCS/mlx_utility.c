/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utility.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:07:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 22:38:20 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>
#include "../libft/libft.h"
#include "../mlx/mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		destroy(t_parse *cub)
{
	mlx_destroy_window(cub->vars.mlx, cub->vars.win);
	exit(0);
	return (1);
}

int		ft_checkposition(t_parse *cub, int x, int y)
{
	if ((x > 0 && x < cub->maxstrlen) || (y > 0 && y < cub->max_y)
			|| (cub->vars.pos_x > 0 && cub->vars.pos_x < cub->maxstrlen)
			|| (cub->vars.pos_y > 0 && cub->vars.pos_y < cub->max_y))
		return (1);
	else
		return (0);
}

void	ft_sort(t_parse *cub)
{
	int		i;
	int		temp;
	double	tempp;

	i = 0;
	temp = 0;
	tempp = 0.0;
	while (i + 1 < cub->objects)
	{
		if (cub->arr[i].distance < cub->arr[i + 1].distance)
		{
			temp = cub->sprite_order[i];
			tempp = cub->arr[i].distance;
			cub->sprite_order[i] = cub->sprite_order[i + 1];
			cub->arr[i].distance = cub->arr[i + 1].distance;
			cub->sprite_order[i + 1] = temp;
			cub->arr[i + 1].distance = tempp;
			i = 0;
		}
		else
			i++;
	}
}

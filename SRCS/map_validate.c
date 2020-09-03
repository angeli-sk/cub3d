/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validate.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:28:53 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 17:00:35 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

static void	ft_floodfill(t_parse *cub, int y, int x)
{
	if (x == 0 || y == 0 || x == cub->maxstrlen || (y + 1) == cub->max_y ||
		cub->mapcopy[y][x + 1] == '\0' || cub->mapcopy[y][x] == '\0')
	{
		ft_exit_c3d(cub, "Floodfill failed :((", 20);
		return ;
	}
	cub->mapcopy[y][x] = 'x';
	if (cub->mapcopy[y - 1][x] != '1' && cub->mapcopy[y - 1][x] != 'x')
		ft_floodfill(cub, y - 1, x);
	if (cub->mapcopy[y - 1][x + 1] != '1' && cub->mapcopy[y - 1][x + 1] != 'x')
		ft_floodfill(cub, y - 1, x + 1);
	if (cub->mapcopy[y][x + 1] != '1' && cub->mapcopy[y][x + 1] != 'x')
		ft_floodfill(cub, y, x + 1);
	if (cub->mapcopy[y + 1][x + 1] != '1' && cub->mapcopy[y + 1][x + 1] != 'x')
		ft_floodfill(cub, y + 1, x + 1);
	if (cub->mapcopy[y + 1][x] != '1' && cub->mapcopy[y + 1][x] != 'x')
		ft_floodfill(cub, y + 1, x);
	if (cub->mapcopy[y + 1][x - 1] != '1' && cub->mapcopy[y + 1][x - 1] != 'x')
		ft_floodfill(cub, y + 1, x - 1);
	if (cub->mapcopy[y][x - 1] != '1' && cub->mapcopy[y][x - 1] != 'x')
		ft_floodfill(cub, y, x - 1);
	if (cub->mapcopy[y - 1][x - 1] != '1' && cub->mapcopy[y - 1][x - 1] != 'x')
		ft_floodfill(cub, y - 1, x - 1);
}

static void	obj_array_fill(t_parse *cub)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	cub->arr = malloc(sizeof(t_array) * cub->objects + 1);
	if (cub->arr == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	while (y < cub->max_y)
	{
		x = 0;
		while (cub->mapcopy[y][x] != '\0')
		{
			if (cub->mapcopy[y][x] == '2')
			{
				ft_bzero(&cub->arr[i], sizeof(t_array));
				cub->arr[i].x = x;
				cub->arr[i].y = y;
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	mapvalidity(t_parse *cub)
{
	playerobjcheck(cub);
	obj_array_fill(cub);
	if (cub->players == 1)
		ft_floodfill(cub, cub->starty, cub->startx);
	else
		ft_exit_c3d(cub, "Map is fricked", 14);
}

void		validity(t_parse *cub)
{
	check_if_empty_start(cub);
	mapvalidity(cub);
}

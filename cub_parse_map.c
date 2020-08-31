#include "./cub3d.h"
#include "./libft/libft.h"
#include "stdlib.h"

void	check_if_empty_start(t_parse *cub) //error
{
	if (cub->rx < 0 || cub->ry < 0)
		ft_exit_c3d(cub, "R is fricked", 12);
	if (cub->no == 0)
		ft_exit_c3d(cub, "NO is fricked", 13);
	if (cub->so == 0)
		ft_exit_c3d(cub, "SO is fricked", 13);
	if (cub->we == 0)
		ft_exit_c3d(cub, "WE is fricked", 13);
	if (cub->ea == 0)
		ft_exit_c3d(cub, "EA is fricked", 13);
	if (cub->s == 0)
		ft_exit_c3d(cub, "S is fricked", 13);
	if (((cub->fr < 0 || cub->fr > 255) || (cub->fg < 0 || cub->fg > 255)
	|| (cub->fb < 0 || cub->fb > 255)))
		ft_exit_c3d(cub, "F is fricked", 12);
	if ((cub->cr < 0 || cub->cr > 255) || (cub->cg < 0 || cub->cg > 255)
	|| (cub->cb < 0 || cub->cb > 255))
		ft_exit_c3d(cub, "C is fricked", 12);
}

void	playerobjcheck(t_parse *cub) //map error
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < cub->max_y)
	{
		while (cub->mapcopy[y][x] != '\0')
		{
			if ((cub->mapcopy[y][x] != 'N' && cub->mapcopy[y][x] != 'S' &&
				cub->mapcopy[y][x] != 'W'
				&& cub->mapcopy[y][x] != 'E') && cub->mapcopy[y][x] != '2'
				&& cub->mapcopy[y][x] != '1' && cub->mapcopy[y][x] != '0' &&
				cub->mapcopy[y][x] != ' ')
				ft_exit_c3d(cub, "Map is fricked", 14);
			if (cub->mapcopy[y][x] == 'S' || cub->mapcopy[y][x] == 'W' ||
				cub->mapcopy[y][x] == 'E' || cub->mapcopy[y][x] == 'N')
			{
				cub->players++;
				cub->ltr = cub->mapcopy[y][x];
				cub->startx = x;
				cub->starty = y;
			}
			if (cub->mapcopy[y][x] == '2')
				cub->objects++;
			x++;
		}
		x = 0;
		y++;
	}
}

void	ft_floodfill(t_parse *cub, int y, int x) //map
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
	if (cub->mapcopy[y + 1][x] != '1'&& cub->mapcopy[y + 1][x] != 'x')
		ft_floodfill(cub, y + 1, x);
	if (cub->mapcopy[y + 1][x - 1] != '1'&& cub->mapcopy[y + 1][x - 1] != 'x')
		ft_floodfill(cub, y + 1, x - 1);
	if (cub->mapcopy[y][x - 1] != '1' && cub->mapcopy[y][x - 1] != 'x')
		ft_floodfill(cub, y, x - 1);
	if (cub->mapcopy[y - 1][x - 1] != '1' && cub->mapcopy[y - 1][x - 1] != 'x')
		ft_floodfill(cub, y - 1, x - 1);
}

void	obj_array_fill(t_parse *cub)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	i = 0;
	cub->arr = malloc(sizeof(t_array) * cub->objects + 1);
	if (cub->arr == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	while (y < cub->max_y)
	{
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
		x = 0;
		y++;
	}
}

void	mapvalidity(t_parse *cub) // map
{
	playerobjcheck(cub);
	obj_array_fill(cub); //to know location of obj
	if (cub->players == 1)
		ft_floodfill(cub, cub->starty, cub->startx);
	else
		ft_exit_c3d(cub, "Map is fricked", 14);
}

void	validity(t_parse *cub)
{
	check_if_empty_start(cub);
	mapvalidity(cub);
	for (int i = 0; i < cub->objects; i++)
		printf("|%d| x = %d && y = %d \n", i, cub->arr[i].x, cub->arr[i].y);
	
}
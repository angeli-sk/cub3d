/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:33:26 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/02 22:34:03 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	cub3d(int argc, char **argv)
{
	t_parse *cub;

	cub = malloc(sizeof(t_parse));
	if (cub == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	cub->save = 0;
	parser(cub, argv, argc);
	if (argc == 3 && !(ft_strncmp(argv[2], "--save", 6)))
	{
		cub->save = 1;
	}
	if (cub->rx > cub->maxrx && cub->save == 0)
		cub->rx = cub->maxrx;
	if (cub->ry > cub->maxry && cub->save == 0)
		cub->ry = cub->maxry;
	if (cub->save == 1 && cub->rx > 16384)
		cub->rx = 16384;
	if (cub->save == 1 && cub->ry > 16384)
		cub->ry = 16384;
	mlx(cub, argv, argc);
	freevars(cub);
	freemaps(cub);
}

int		main(int argc, char **argv)
{
	cub3d(argc, argv);
	return (0);
}

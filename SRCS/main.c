/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:33:26 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 17:47:21 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>

static void	errorsies(char *str)
{
	write(2, "ERROR\n", 6);
	write(2, str, ft_strlen(str));
	exit(1);
}

void		cub3d(int argc, char **argv)
{
	t_parse *cub;

	cub = ft_calloc(1, sizeof(t_parse));
	if (cub == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	cub->save = 0;
	parser(cub, argv, argc);
	if (argc == 3 && !(ft_strncmp(argv[2], "--save", 7)))
		cub->save = 1;
	if (cub->rx > cub->maxrx && cub->save == 0)
		cub->rx = cub->maxrx;
	if (cub->ry > cub->maxry && cub->save == 0)
		cub->ry = cub->maxry;
	if (cub->save == 1 && cub->rx > 16384)
		cub->rx = 16384;
	if (cub->save == 1 && cub->ry > 16384)
		cub->ry = 16384;
	if (cub->ry <= 0 || cub->rx <= 0)
		errorsies("R is fricked\n");
	mlx(cub, argv, argc);
	exit(0);
}

int			main(int argc, char **argv)
{
	int len;

	if (argc != 2 && argc != 3)
		errorsies("wrong args lemao\n");
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 7)))
		errorsies("wrong args lemao\n");
	len = ft_strlen(argv[1]);
	if (len < 4)
		errorsies("no .cub yo\n");
	if (ft_strncmp(argv[1] + len - 4, ".cub", 5))
		errorsies("no .cub yo\n");
	cub3d(argc, argv);
	return (0);
}

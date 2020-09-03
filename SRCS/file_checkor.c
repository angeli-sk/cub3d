/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_checkor.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 20:10:50 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 21:36:27 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>
#include <fcntl.h>

static void	open_file(char *str, t_parse *cub)
{
	int fd;

	fd = open(str, O_RDWR);
	if (fd == -1)
		ft_exit_c3d(cub, "File does not exist", 19);
	close(fd);
}

void		file_checkor(t_parse *cub)
{
	open_file(cub->no, cub);
	open_file(cub->so, cub);
	open_file(cub->we, cub);
	open_file(cub->ea, cub);
	open_file(cub->s, cub);
}

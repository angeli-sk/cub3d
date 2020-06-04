/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/06/04 17:50:30 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "./get_next_line/get_next_line.h"

int	main(void)
{
	int fd;
	char *line;

	fd = open("map.cub", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
	}
	close(fd);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/04 21:04:29 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./cub3d.h"

void	num_check(int *i, char **line, int *start)
{
	while (((*line)[*i] < '0') || ((*line)[*i] > '9'))
		(*i)++;
	*start = *i;
	while (((*line)[*i] >= '0') && ((*line)[*i] <= '9'))
		(*i)++;
}

void	struct_num(char **line, int *adr1, int *adr2, int *adr3)
{
	int		start;
	int		check;
	char	*temp;
	int		i;

	start = 0;
	check = 1;
	i = 0;
	while ((*line)[i] != '\0')
	{
		num_check(&i, line, &start);
		temp = malloc((i - start) * sizeof(char) + 1);
		ft_strlcpy(temp, &(*line)[start], (i - start) + 1);
		if (check == 1)
			*adr1 = ft_atoi(temp);
		if (check == 2)
			*adr2 = ft_atoi(temp);
		if (check == 3)
			*adr3 = ft_atoi(temp);
		free(temp);
		check++;
		i++;
	}
}

char	*struct_path(t_cub3d *cub, int i, char **line)
{
	int		len;
	char	*temp;

	while ((*line)[i] != '.')
		i++;
	len = ft_strlen(&(*line)[i]);
	temp = malloc((sizeof(char) * len) + 1);
	temp[len] = '\0';
	ft_strlcpy(temp, &(*line)[i], len);
	return (temp);
}

int		read_map(t_cub3d *cub, char *line, int i, int ret)
{
	int chk;
	int len;

	chk = 0;
	if (cub->temp == 0)
		chk = 1;
	cub->temp = ft_strjoin_c3d(cub->temp, line);
	if (chk == 1)
	{
		len = ft_strlen(cub->temp);
		cub->temp[len] = '\n';
		cub->temp[len + 1] = '\0';
	}
	printf("~~temp=%s && line=%s\n~~", cub->temp, line);
	ret++;
	return (ret);
}

void	struct_init(t_cub3d *cub)
{
	cub->RX = 0;
	cub->RY = 0;
	cub->NO = 0;
	cub->SO = 0;
	cub->WE = 0;
	cub->EA = 0;
	cub->S = 0;
	cub->FR = 0;
	cub->FG = 0;
	cub->FB = 0;
	cub->CR = 0;
	cub->CG = 0;
	cub->CB = 0;
	cub->temp = 0;
	cub->map = 0;
}

int		jumping(char *line, t_cub3d *cub, int i, int ret)
{
	if ((line[i] == 'R' && line[i + 1] == ' '))
		struct_num(&line, &cub->RX, &cub->RY, &cub->RY);
	if (line[i] == 'N' && line[i + 1] == 'O')
		cub->NO = struct_path(cub, i, &line);
	if (line[i] == 'S' && line[i + 1] == 'O')
		cub->SO = struct_path(cub, i, &line);
	if (line[i] == 'W' && line[i + 1] == 'E')
		cub->WE = struct_path(cub, i, &line);
	if (line[i] == 'E' && line[i + 1] == 'A')
		cub->EA = struct_path(cub, i, &line);
	if (line[i] == 'S' && line[i + 1] == ' ')
		cub->S = struct_path(cub, i, &line);
	if (line[i] == 'F' && line[i + 1] == ' ')
		struct_num(&line, &cub->FR, &cub->FG, &cub->FB);
	if (line[i] == 'C' && line[i + 1] == ' ')
		struct_num(&line, &cub->CR, &cub->CG, &cub->CB);
	if (line[i] == '0' || line[i] == '1')
		ret = read_map(cub, line, i, ret);
	return (ret);
}

void	freevars(char *line, t_cub3d *cub)
{
	free(line);
	free(cub->NO);
	free(cub->SO);
	free(cub->WE);
	free(cub->EA);
	free(cub->S);
	free(cub->temp);
}

int	mapping(char *line, t_cub3d *cub)
{
	int fd;
	int i;
	int retval;
	int ret;

	fd = open("map.cub", O_RDONLY);
	i = 0;
	ret = 0;
	line = NULL;
	struct_init(cub);
	retval = 1;
	while (retval == 1)
	{
		retval = get_next_line(fd, &line);
		while (line[i] == ' ' || line[i] == '\t')	
			i++;
		ret = jumping(line, cub, i, ret);
		i = 0;
		if (retval == 1)
			free(line);
	}
	cub->map = ft_split(cub->temp, '\n');
	close(fd);
	return (ret);
}

int	checkborder(t_cub3d *cub, int x, int y, int ret)
{
	int error;

	error = 0;
	while (y == 0 && cub->map[y][x] != '\n')
	{
		if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
			error = -1;
		x++;
	}
	x = 0;
	while (y > 0 && y < ret && cub->map[y][x] != '\n')
	{
		if (cub->map[y][0] != '1' && cub->map[y][0] != ' ')
			error = -1;
		x++;
	}
	x = 0;
	while (y == ret && cub->map[y][x] != '\n')
	{
		if (cub->map[y][x] != '1')
			error = -1;
		x++;
	}
	return (error);
}

void	validity(t_cub3d *cub, int ret)
{
	int x;
	int y;
	int error;

	x = 0;
	y = 0;
	error = 0;
	//printf("ret = %d", ret);
	while (y < ret)
	{
		while (cub->map[y][x] == ' ' || cub->map[y][x] == '\t')
			x++;
		error = checkborder(cub, x, y, ret);
		// error = checkplayer();
		// if (error == -1)
		// 	novalidmapyo();
		//printf("\nMAPPOINTIETS = %c & x = %d & y = %d\n", cub->map[y][x], x, y);
		y++;
		x = 0;
	}
	//printf("\nMAPPOINTIETS = %c & x = %d & y = %d\n", cub->map[y][x], x, y);
}

void	cub3d(void)
{
	char	*line;
	t_cub3d cub;
	int ret;

	ret = mapping(line, &cub);
	cub.map = ft_split(cub.temp, '\n');
	freevars(line, &cub);
	validity(&cub, ret);
}

int		main(void)
{
	cub3d();
	// while(1)
	// ;
	return (0);
}


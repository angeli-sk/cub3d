/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/15 19:34:00 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./cub3d.h"

int	num_check(int *i, char **line, int *start, int error)
{
	while (((*line)[*i] < '0') || ((*line)[*i] > '9'))
	{
		if ((*line)[*i] == ' ')
			(*i)++;
		else
			error = -2;
	}	
	*start = *i;
	while (((*line)[*i] >= '0') && ((*line)[*i] <= '9'))
		(*i)++;
	return (error);
}

int		ft_error_res(int num, int error) //error checker for correct resolution
{
	if (num <= 0)
		error = -2;
	//check if rmax screen res is okay
	if (error != 0)
		ft_error_c3d();
	return (error);
}

void	ft_error_c3d(int error)
{
	if (error == -2)
		write(1, "R is fricked", 12);
	exit();
}

int	strcut_num_loopcheck(int *adr, int error, char *temp)
{
	*adr = ft_atoi(temp);
	error = ft_error_res(*adr, error);
	return (error);
}

void	struct_num(char **line, int *adr1, int *adr2, int *adr3)
{
	int		start;
	int		check;
	char	*temp;
	int		i;
	int		error;

	start = 0;
	check = 1;
	i = 0;
	error = 0;
	while ((*line)[i] != '\0')
	{
		num_check(&i, line, &start, error);
		temp = malloc((i - start) * sizeof(char) + 1);
		ft_strlcpy(temp, &(*line)[start], (i - start) + 1);
		if (check == 1)
			error = strcut_num_loopcheck(adr1, error, temp);
		if (check == 2)
			error = strcut_num_loopcheck(adr2, error, temp);
		if (check == 3)
			error = strcut_num_loopcheck(adr3, error, temp);
		free(temp);
		check++;
		i++;
	}
}

char	*struct_path(t_cub3d *cub, char **line)
{
	int		len;
	char	*temp;

	while ((*line)[(cub->i)] != '.')
		(cub->i)++;
	len = ft_strlen(&(*line)[(cub->i)]);
	temp = malloc((sizeof(char) * len) + 1);
	temp[len] = '\0';
	ft_strlcpy(temp, &(*line)[(cub->i)], len);
	return (temp);
}

int		read_map(t_cub3d *cub, char *line, int ret)
{
	int chk;
	int len;

	chk = 0;
	if (cub->temp == 0)
		chk = 1;
	cub->temp = ft_strjoin_c3d(cub, cub->temp, line);
	printf("\naxlne = %d\n", cub->maxstrlen);
	if (chk == 1)
	{
		len = ft_strlen(cub->temp);
		cub->maxstrlen = len;
		cub->temp[len] = '\n';
		cub->temp[len + 1] = '\0';
	}
	printf("~~temp=%s && line=%s\n~~", cub->temp, line);
	ret++;
	return (ret);
}

void	struct_init(t_cub3d *cub)
{
	cub->rx = 0;
	cub->ry = 0;
	cub->no = 0;
	cub->so = 0;
	cub->we = 0;
	cub->ea = 0;
	cub->s = 0;
	cub->fr = 0;
	cub->fr = 0;
	cub->fb = 0;
	cub->cr = 0;
	cub->cg = 0;
	cub->cb = 0;
	cub->temp = 0;
	cub->map = 0;
	cub->error = 0;
	cub->i = 0;
	cub->maxstrlen = 0;
}

int		jumping(char *line, t_cub3d *cub, int ret)
{
	if ((line[(cub->i)] == 'R' && line[(cub->i) + 1] == ' '))
		struct_num(&line, &cub->rx, &cub->ry, &cub->ry);
	if (line[(cub->i)] == 'N' && line[(cub->i) + 1] == 'O')
		cub->no = struct_path(cub, &line);
	if (line[(cub->i)] == 'S' && line[(cub->i) + 1] == 'O')
		cub->so = struct_path(cub, &line);
	if (line[(cub->i)] == 'W' && line[(cub->i) + 1] == 'E')
		cub->we = struct_path(cub, &line);
	if (line[(cub->i)] == 'E' && line[(cub->i) + 1] == 'A')
		cub->ea = struct_path(cub, &line);
	if (line[(cub->i)] == 'S' && line[(cub->i) + 1] == ' ')
		cub->s = struct_path(cub, &line);
	if (line[(cub->i)] == 'F' && line[(cub->i) + 1] == ' ')
		struct_num(&line, &cub->fr, &cub->fr, &cub->fb);
	if (line[(cub->i)] == 'C' && line[(cub->i) + 1] == ' ')
		struct_num(&line, &cub->cr, &cub->cg, &cub->cb);
	if (line[(cub->i)] == '0' || line[(cub->i)] == '1')
		ret = read_map(cub, line, ret);
	// else
	// 	cub->error = -1; //do sumthng with this lazy ass
	return (ret);
}

void	freevars(char *line, t_cub3d *cub)
{
	free(line);
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	free(cub->s);
	free(cub->temp);
}

int	mapping(char *line, t_cub3d *cub)
{
	int fd;
	int retval;
	int ret;

	fd = open("map.cub", O_RDONLY);
	ret = 0;
	line = NULL;
	struct_init(cub);
	retval = 1;
	while (retval == 1)
	{
		retval = get_next_line(fd, &line);
		while (line[cub->i] == ' ')
			(cub->i)++;
		ret = jumping(line, cub, ret);
		if (retval == 1)
			free(line);
	}
	cub->map = ft_split_c3d(cub, cub->temp, '\n');
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
	printf("ret = %d", ret);
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
	int i =0;
	ret = mapping(line, &cub);
	cub.map = ft_split(cub.temp, '\n');
	while (i <= 13)
	{
		printf("==%s\n",(cub.map)[i]);
		i++;
	}

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


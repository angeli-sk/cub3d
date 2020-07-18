/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/18 22:49:14 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./cub3d.h"

int	num_check(int *i, char **line, int *start, int error)
{
	char letter;

	while (((*line)[*i] < '0') || ((*line)[*i] > '9'))
	{
		//printf("||c=%c||\n||d=%d||\n||s=%s||\n",(*line)[*i], *i, &(*line)[*i]);
		
		if ((*line)[*i] == ' ' || (*line)[*i] == 'R' || (*line)[*i] == 'F' || (*line)[*i] == 'C')
		{
			if ((*line)[*i] == 'R' || (*line)[*i] == 'F' || (*line)[*i] == 'C')
				letter = (*line)[*i];
			(*i)++;
		}
		else
		{
			printf("\n\nletter = %c\n\n", letter);
			if (letter == 'R')
				error = -2;
			if (letter == 'F')
				error = -3;
			if (letter == 'C')
				error = -4;
			else
				error = -17;
			break ;
		}
	}	//printf("lemao");
	*start = *i;
	while (((*line)[*i] >= '0') && ((*line)[*i] <= '9'))
		(*i)++;
	return (error);
}

void	ft_error_c3d(int error)
{
	printf("error = %d\n", error);
	if (error == -2)
		write(1, "ERROR;\tR is fricked\n", 20);
	if (error == -3)
		write(1, "ERROR;\tF is fricked\n", 20);
	if (error == -4)
		write(1, "ERROR;\tC is fricked\n", 20);
	if (error == -5)
		write(1, "ERROR;\tNO is fricked\n", 21);
	if (error == -6)
		write(1, "ERROR;\tSO is fricked\n", 21);
	if (error == -7)
		write(1, "ERROR;\tWE is fricked\n", 21);
	if (error == -8)
		write(1, "ERROR;\tEA is fricked\n", 21);
	if (error == -9)
		write(1, "ERROR;\tS is fricked\n", 20);
	if (error == -17)
		write(1, "ERROR;\t??? is fricked\n", 22);
	printf("LEMAO");
	exit(1);
}

int		ft_error_res(int num, int error) //error checker for correct resolution
{
	if (num <= 0)
		error = -2;
	//check if rmax screen res is okay
	if (error != 0)
		ft_error_c3d(error);
	return (error);
}

int	strcut_num_loopcheck(int *adr, int error, char *temp)
{
	*adr = ft_atoi(temp);
	//error = ft_error_res(*adr, error);
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
		while (((*line)[i] < '0') || ((*line)[i] > '9'))
			i++;
		error = num_check(&i, line, &start, error);
		if (error != 0)
			ft_error_c3d(error);
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
	ft_strlcpy(temp, &((*line)[(cub->i)]), len + 1);
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
	//printf("\naxlne = %d\n", cub->maxstrlen);
	if (chk == 1)
	{
		len = ft_strlen(cub->temp);
		cub->maxstrlen = len;
		cub->temp[len] = '\n';
		cub->temp[len + 1] = '\0';
	}
	//printf("~~temp=%s && line=%s\n~~", cub->temp, line);
	ret++;
	return (ret);
}

void	struct_init(t_cub3d *cub)
{
	cub->rx = -1;
	cub->ry = -1;
	cub->no = 0;
	cub->so = 0;
	cub->we = 0;
	cub->ea = 0;
	cub->s = 0;
	cub->fr = -1;
	cub->fr = -1;
	cub->fb = -1;
	cub->cr = -1;
	cub->cg = -1;
	cub->cb = -1;
	cub->temp = 0;
	cub->map = 0;
	cub->error = -1;
	cub->i = -1;
	cub->maxstrlen = -1;
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
		struct_num(&line, &cub->fr, &cub->fg, &cub->fb);
	if (line[(cub->i)] == 'C' && line[(cub->i) + 1] == ' ')
		struct_num(&line, &cub->cr, &cub->cg, &cub->cb);
	if (line[(cub->i)] == '0' || line[(cub->i)] == '1')
		ret = read_map(cub, line, ret);
	// else
	// 	cub->error = -1; //do sumthng with this lazy ass
	return (ret);
}

void	freevars(char *line, t_cub3d *cub, int ret)
{
	int i;

	i = 0;
	free(line);
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	free(cub->s);
	free(cub->temp);
	while (i <= ret)
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
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
		(cub->i) = 0;
		retval = get_next_line(fd, &line);
		while (line[cub->i] == ' ')
			(cub->i)++;
		ret = jumping(line, cub, ret);
		if (retval == 1)
			free(line);
	}
	free(line);
	//printf("=-=%s=-=\n", cub->temp);
	cub->map = ft_split_c3d(cub, cub->temp, '\n');
	close(fd);
	return (ret);
}

// int	checkborder(t_cub3d *cub, int x, int y, int ret)
// {
// 	int error;

// 	error = 0;
// 	while (y == 0 && cub->map[y][x] != '\n')
// 	{
// 		if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
// 			error = -1;
// 		x++;
// 	}
// 	x = 0;
// 	while (y > 0 && y < ret && cub->map[y][x] != '\n')
// 	{
// 		if (cub->map[y][0] != '1' && cub->map[y][0] != ' ')
// 			error = -1;
// 		x++;
// 	}
// 	x = 0;
// 	while (y == ret && cub->map[y][x] != '\n')
// 	{
// 		if (cub->map[y][x] != '1')
// 			error = -1;
// 		x++;
// 	}
// 	return (error);
// }

void	check_if_empty(t_cub3d *cub)
{
	if (cub->rx == 0 || cub->ry == 0)
		cub->error = -2;
	if (cub->no == 0)
		cub->error = -5;
	if (cub->so == 0)
		cub->error = -6;
	if(cub->we == 0)
		cub->error = -7;
	if(cub->ea == 0)
		cub->error = -8;
	if(cub->s == 0)
		cub->error = -9;
	if((cub->fr < 0 || cub->fr > 255) || (cub->fg < 0 || cub->fg > 255)
	|| (cub->fb < 0 || cub->fb > 255))
		cub->error = -3;
	if((cub->cr < 0 || cub->cr > 255) || (cub->cg < 0 || cub->cg > 255)
	|| (cub->cb < 0 || cub->cb > 255))
	{
		cub->error = -4;
		printf("XINO\n");
	}	
}

void	validity(t_cub3d *cub)
{
	check_if_empty(cub);
	ft_error_c3d(cub->error);
}

void	cub3d(void)
{
	char	*line;
	t_cub3d cub;
	int ret;
	//int i =0;
	ret = mapping(line, &cub);
	//printf("ret=%d\n", ret);
	// while (i < ret)
	// {
	// 	printf("==%s\n",(cub.map)[i]);
	// 	i++;
	// }
	//printf("lemao\n");
	printf("RX=%d\nRY=%d\nNO=%s\nSO=%s\nWE=%s\nEA=%s\nS=%s\n", cub.rx, cub.ry, cub.no, cub.so, cub.we, cub.ea, cub.s);
	printf("Fr=%i\nFg=%i\nFb=%i\nC=%i\nCg=%i\nCb=%i\n",cub.fr, cub.fg, cub.fb, cub.cr, cub.cg, cub.cb);
	freevars(line, &cub, ret);
	validity(&cub);
}

int		main(void)
{
	cub3d();
	// while(1)
	// ;
	return (0);
}


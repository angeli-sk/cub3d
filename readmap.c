/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/06/30 14:50:33 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./get_next_line/get_next_line.h"
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
		if (temp == 0)
			ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
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

	i = i + 2;
	
	while ((*line)[i] == ' ')
		i++;
	printf("|lol|%s|\n", &(*line)[i]);
	len = ft_strlen(&(*line)[i]);
	temp = malloc((sizeof(char) * len) + 1);
	if (temp == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	temp[len] = '\0';
	ft_strlcpy(temp, &(*line)[i], len);
	return (temp);
}

void	read_map(t_cub3d *cub, char *line, int i, t_list map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (cub->((map[y][x]) != ' ')
		x++;
	printf("\nMAPPOINTIETS = %c\n");
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

void	cub3d(void)
{
	int fd;
	int i;
	int retval;
	char *line;
	t_cub3d cub;
	t_list *map;
	
	fd = open("map.cub", O_RDONLY);
	i = 0;
	line = NULL;
	struct_init(&cub);
	retval = 1;
	while (retval == 1)
	{
		retval = get_next_line(fd, &line);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		//printf("\nline[i]=%c && i=%d && line=%s\n", line[i], i, line);
		if ((line[i] == 'R' && line[i + 1] == ' '))
			struct_num(&line, &cub.RX, &cub.RY, &cub.RY);
		if (line[i] == 'N' && line[i + 1] == 'O')
			cub.NO = struct_path(&cub, i, &line);
		if (line[i] == 'S' && line[i + 1] == 'O')
			cub.SO = struct_path(&cub, i, &line);
		if (line[i] == 'W' && line[i + 1] == 'E')
			cub.WE = struct_path(&cub, i, &line);
		if (line[i] == 'E' && line[i + 1] == 'A')
			cub.EA = struct_path(&cub, i, &line);
		if (line[i] == 'S' && line[i + 1] == ' ')
			cub.S = struct_path(&cub, i, &line);
		if (line[i] == 'F' && line[i + 1] == ' ')
			struct_num(&line, &cub.FR, &cub.FG, &cub.FB);
		if (line[i] == 'C' && line[i + 1] == ' ')
			struct_num(&line, &cub.CR, &cub.CG, &cub.CB);
		if (line[i] == '0' || line[i] == '1')
		{
			printf("\nline[i]=%c && i=%d && line=%s\n", line[i], i, line);
			read_map(&cub, line, i);
		}
		printf("BRUHH%s\n", line);
		printf("\nRX = %d\nRY = %d\n", cub.RX, cub.RY);
		i = 0;
		if (retval == 1)
			free(line);
	}
	//if (cub.map == 0)
	//	cub.map = malloc (1);
	cub.map = ft_split(cub.temp, '\n');
	printf("\ncub.NO=%s\n", cub.NO);
	printf("\ncub.SO=%s\n", cub.SO);
	printf("\ncub.WE=%s\n", cub.WE);
	printf("\ncub.EA=%s\n", cub.EA);
	printf("\ncub.S=%s\n", cub.S);
	printf("\nFR = %d\nFG = %d\nFB = %d\n", cub.FR, cub.FG, cub.FB);
	printf("\nCR = %d\nCG = %d\nCB = %d\n", cub.CR, cub.CG, cub.CB);
	free(line);
	free(cub.NO);
	free(cub.SO);
	free(cub.WE);
	free(cub.EA);
	free(cub.S);
	free(cub.temp);
	// int y = 0;
	// while (y < 14){
	// 	printf("y = %d\t===%s===\n", y, map[y]);
	// 	y++;
	//}
	
	close(fd);
}

int		main(void)
{
	cub3d();
	while(1)
	;
	return (0);
}


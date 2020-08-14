/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/08/07 22:34:01 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./cub3d.h"

void	freemaps(t_cub3d *cub)
{
	// int i;

	// i = 0;
	while (cub->max_y >= 0 && (cub->map || cub->mapcopy))
	{
		//if (!(cub->map[i]))
			free(cub->map[cub->max_y]);
		//if (!(cub->mapcopy[i]))
			free(cub->mapcopy[cub->max_y]);
		cub->max_y--;
	}
	//if (!(cub->map))
		free(cub->map);
	//if (!(cub->mapcopy))
		free(cub->mapcopy);
}

void	freevars(t_cub3d *cub)
{
	if ((cub->line != 0))
		free((cub->line));
	if ((cub->no != 0))
		free(cub->no);
	if ((cub->so != 0))
		free(cub->so);
	if ((cub->we != 0))
		free(cub->we);
	if(cub->ea != 0)
		free(cub->ea);
	if ((cub->s != 0))
		free(cub->s);
	if (cub->temp != 0)
		free(cub->temp);
}

void	ft_write_error(char *s, int len)
{
	write (1, "ERROR\n", 6);
	write (1, s, len);
	write(1, "\n", 1);
}

void	ft_exit_c3d(t_cub3d *cub, char *s, int len)
{
	write (1, "ERROR\n", 6);
	write (1, s, len);
	write(1, "\n", 1);
	freevars(cub);
	if (cub->beginmap != 0)
		freemaps(cub);
	close(cub->fd);
	exit(1);
}



void num_check_p2(t_struct_num *snum, t_cub3d *cub)
{
	if (snum->ltr == 'R')
		ft_exit_c3d(cub, "R is fricked", 12);
	else if (snum->ltr == 'F')
		ft_exit_c3d(cub, "F is fricked", 12);
	else if (snum->ltr == 'C')
		ft_exit_c3d(cub, "C is fricked", 12);
	else
		ft_exit_c3d(cub, "? is fricked", 12);
}

void	ft_check_if_numcorrect(t_struct_num *snum, t_cub3d *cub)
{
	int tempi;

	tempi = 0;
	while ((snum->ltr == 'R' && (cub->line)[tempi] != '\0') )
	{
		if ((cub->line)[tempi] == ',')
				ft_exit_c3d(cub, "R is fricked", 12);
		tempi++;
	}
	tempi = snum->st;
	while (((snum->ltr == 'F' || snum->ltr == 'C') && (cub->line)[tempi] != '\0') )
	{
		if (ft_isspace((cub->line)[tempi]) == 1)
		{
			if (snum->ltr == 'F')
				ft_exit_c3d(cub, "F is fricked", 12);
			else
				ft_exit_c3d(cub, "C is fricked", 12);
		}
		tempi++;
	}
}

void	num_check(t_struct_num *snum, t_cub3d *cub)
{
	while (((cub->line)[snum->i] < '0') || ((cub->line)[snum->i] > '9'))
	{
		if ((snum->error) != too_many_nums && ((cub->line)[snum->i] == ' '
		|| ((cub->line)[snum->i] == ',' && (cub->line)[snum->i + 1] != ',')
		|| (cub->line)[snum->i] == 'R' || (cub->line)[snum->i] == 'F'
		|| (cub->line)[snum->i] == 'C'))
		{
			if ((cub->line)[snum->i] == 'R' || (cub->line)[snum->i] == 'F'
			|| (cub->line)[snum->i] == 'C')
			{
				snum->ltr = (cub->line)[snum->i];
				if (snum->ltr == 'F' && cub->f == 0)
					cub->f = 1;
				else if (snum->ltr == 'F' && cub->f == 1)
					ft_exit_c3d(cub, "F is fricked", 12);
				if (snum->ltr == 'C' && cub->c == 0)
					cub->c = 1;
				else if (snum->ltr == 'C' && cub->c == 1)
					ft_exit_c3d(cub, "C is fricked", 12);
				if (snum->ltr == 'R' && cub->r == 0)
					cub->r = 1;
				else if (snum->ltr == 'R' && cub->r == 1)
					ft_exit_c3d(cub, "R is fricked", 12);
			}	
			if (snum->check > 2 && snum->ltr == 'R')
				ft_exit_c3d(cub, "R is fricked", 12);
			(snum->i)++;
		}
		else
		{
			num_check_p2(snum, cub);
			break ;
		}
	}
	snum->st = snum->i;
	while ((((cub->line))[snum->i] >= '0') && (((cub->line))[snum->i] <= '9'))
		(snum->i)++;
	ft_check_if_numcorrect(snum, cub);
}

// int		ft_error_res(int num, int error) //error checker for correct resolution
// {
// 	if (num <= 0)
// 		error = -2;
// 	//check if rmax screen res is okay
// 	if (error != 0)
// 		ft_exit_c3d(error);
// 	return (error);
// }

void	struct_num_init(t_struct_num *snum)
{
	snum->st = 0;
	snum->check = 1;
	snum->i = 0;
	snum->error = 0;
	snum->temp = 0;
	snum->ltr = 0;
}

void	struct_num(t_cub3d *cub, int *adr1, int *adr2, int *adr3)
{
	t_struct_num snum;

	struct_num_init(&snum);
	while ((cub->line)[snum.i] != '\0')
	{
		if (snum.check > 3)
			snum.error = too_many_nums; //check if this still works with 2 and 3 nums
		num_check(&snum, cub);
		snum.temp = malloc(((snum.i) - (snum.st)) * sizeof(char) + 1);
		ft_strlcpy(snum.temp, &(cub->line)[snum.st], ((snum.i) - (snum.st)) + 1);
		if (snum.check == 1)
			*adr1 = ft_atoi(snum.temp);
		if (snum.check == 2)
			*adr2 = ft_atoi(snum.temp);
		if (snum.check == 3)
			*adr3 = ft_atoi(snum.temp);
		free(snum.temp);
		snum.check++;
	}
}

void		check_if_s_empty(t_cub3d *cub)
{
	if ((cub->line)[(cub->i)] == 'N' && (cub->line)[(cub->i) + 1] == 'O'
			&& cub->no != 0)
		ft_exit_c3d(cub, "NO is fricked", 13);
	else if ((cub->line)[(cub->i)] == 'S' && (cub->line)[(cub->i) + 1] == 'O'
			&& cub->so != 0)
		ft_exit_c3d(cub, "SO is fricked", 13);
	else if ((cub->line)[(cub->i)] == 'W' && (cub->line)[(cub->i) + 1] == 'E'
			&& cub->we != 0)
		ft_exit_c3d(cub, "WE is fricked", 13);
	else if ((cub->line)[(cub->i)] == 'E' && (cub->line)[(cub->i) + 1] == 'A'
			&& cub->ea != 0)
		ft_exit_c3d(cub, "EA is fricked", 13);
	else if ((cub->line)[(cub->i)] == 'S' && (cub->line)[(cub->i) + 1] == ' '
			&& cub->s != 0)
		ft_exit_c3d(cub, "S is fricked", 12);
	else
		return;
}

char	*struct_path(t_cub3d *cub)
{
	int		len;
	char	*temp;
	int		tempi;

	len = 0;
	tempi = 0;
	while ((cub->line)[(cub->i)] == ' ')
		(cub->i)++;
	check_if_s_empty(cub);
	tempi = cub->i;
	while((cub->line)[tempi] != '\0')
		tempi++;
	len = ft_strlen(&(cub->line)[(cub->i)]);
	temp = malloc((sizeof(char) * len) + 1);
	temp[len] = '\0';
	ft_strlcpy(temp, &((cub->line)[(cub->i)]), len + 1);
	return (temp);
}

void		read_map(t_cub3d *cub)
{
	int chk;
	int len;

	chk = 0;
	if (cub->temp == 0)
		chk = 1;
	//printf("line = %s\n", line);
	cub->temp = ft_strjoin_c3d(cub, cub->temp, cub->line);
	//printf("LINE=[[%s]]\nTEMP=[%s]\n", line, cub->temp);
	if (chk == 1)
	{
		len = ft_strlen(cub->temp);
		cub->maxstrlen = len;
		cub->temp[len] = '\n';
		cub->temp[len + 1] = '\0';
	}
	cub->max_y++;
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
	cub->mapcopy = 0;
	cub->error = 0;
	cub->beginmap = 0;
	cub->i = -1;
	cub->maxstrlen = -1;
	cub->maxrx = 1920;			//add function that actually calculates dis bish
	cub->maxry = 1080;
	cub->players = 0;
	cub->objects = 0;
	cub->startx = 0;
	cub->starty = 0;
	cub->max_y = 0;
	cub->line = 0;
	cub->r = 0;
	cub->f = 0;
	cub->c = 0;
	cub->fd = 0;
}

int	ft_checkmapplacement(t_cub3d *cub)
{
	if (cub->rx == -1 || cub->ry == -1 || cub->no == 0 || cub->so == 0
	|| cub->we == 0 || cub->ea == 0 || cub->s == 0 || cub->fr == -1
	|| cub->fg == -1 || cub->fb == -1 || cub->cr == -1 || cub->cg == -1
	|| cub->cb == -1)
	{
		ft_exit_c3d(cub, "You fool, check your .cub file again :00", 40);
		return (-1);
	}
	return (0);
}

void		parsing(t_cub3d *cub, int ret)
{
	if (((cub->line)[(cub->i)] == 'R' && (cub->line)[(cub->i) + 1] == ' '))
		struct_num(cub, &cub->rx, &cub->ry, &cub->ry);
	else if ((cub->line)[(cub->i)] == 'N' && (cub->line)[(cub->i) + 1] == 'O')
		cub->no = struct_path(cub);
	else if ((cub->line)[(cub->i)] == 'S' && (cub->line)[(cub->i) + 1] == 'O')
		cub->so = struct_path(cub);
	else if ((cub->line)[(cub->i)] == 'W' && (cub->line)[(cub->i) + 1] == 'E')
		cub->we = struct_path(cub);
	else if ((cub->line)[(cub->i)] == 'E' && (cub->line)[(cub->i) + 1] == 'A')
		cub->ea = struct_path(cub);
	else if ((cub->line)[(cub->i)] == 'S' && (cub->line)[(cub->i) + 1] == ' ')
		cub->s = struct_path(cub);
	else if ((cub->line)[(cub->i)] == 'F' && (cub->line)[(cub->i) + 1] == ' ')
		struct_num(cub, &cub->fr, &cub->fg, &cub->fb);
	else if ((cub->line)[(cub->i)] == 'C' && (cub->line)[(cub->i) + 1] == ' ')
		struct_num(cub, &cub->cr, &cub->cg, &cub->cb);
	else if ((cub->line)[(cub->i)] == '0' || (cub->line)[(cub->i)] == '1')
	{
		if (cub->beginmap == 0)
			cub->beginmap = 1;
		if (ft_checkmapplacement(cub) == 0)
			read_map(cub);
	}
	else if ((cub->line)[(cub->i)] != '\0' && cub->beginmap == 0)
		cub->error = invalid_char;
	if ((cub->line)[(cub->i)] == '\0' && cub->beginmap == 1)
		cub->beginmap = 2;
	if ((cub->line)[(cub->i)] != '\0' && cub->beginmap == 2)
		cub->error = invalid_map;
}

void	readfile(t_cub3d *cub, char *path)
{
	int ret;
	
	cub->fd = open(path, O_RDONLY);
	if (cub->fd < 0)
		ft_exit_c3d(cub, "Open failed; lemao defrick, how??", 33);
	ret = 1;
	while (ret == 1)
	{
		(cub->i) = 0;
		ret = get_next_line(cub->fd, &(cub->line));
		while ((cub->line)[cub->i] == ' ')
			(cub->i)++;
		parsing(cub, cub->max_y);
		if (ret == 1)
			free((cub->line));
	}
	//free((cub->line));
	if (cub->error == invalid_map)
		ft_exit_c3d(cub, "Your map is fricked", 19);
	if (cub->error == invalid_char)
		ft_exit_c3d(cub, "There's sum garbo man, clean it", 31);
	cub->map = ft_split_c3d(cub, cub->temp, '\n');
	cub->mapcopy = ft_split_c3d(cub, cub->temp, '\n');
	//close(fd);
}

void	check_if_empty_start(t_cub3d *cub)
{
	if ((cub->rx < 0 || cub->rx > cub->maxrx)
	|| (cub->ry < 0 || cub->ry > cub->maxry))
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

void	playerobjcheck(t_cub3d *cub)
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

void	ft_floodfill(t_cub3d *cub, int y, int x)
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

void	mapvalidity(t_cub3d *cub)
{
	playerobjcheck(cub);
	if (cub->players == 1)
		ft_floodfill(cub, cub->starty, cub->startx);
	else
		ft_exit_c3d(cub, "Map is fricked", 14);
}

void	validity(t_cub3d *cub)
{
	check_if_empty_start(cub);
	mapvalidity(cub);
}

void	cub3d(char **argv, int argc)
{
	t_cub3d cub;

	if (argc < 2 || argc > 3)
		ft_exit_c3d(&cub, "Not the right amount of arguments", 33);
	struct_init(&cub);
	readfile(&cub, argv[1]);//make error function for this too many args too litlle etc
	printf("lemao\n");
	printf("RX=%d\nRY=%d\nNO=%s\nSO=%s\nWE=%s\nEA=%s\nS=%s\n", cub.rx, cub.ry, cub.no, cub.so, cub.we, cub.ea, cub.s);
	printf("Fr=%i\nFg=%i\nFb=%i\nC=%i\nCg=%i\nCb=%i\n",cub.fr, cub.fg, cub.fb, cub.cr, cub.cg, cub.cb);
	validity(&cub);
	int i = 0;
	while (i < cub.max_y)
	{
		printf("==%s\n",(cub.mapcopy)[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < cub.max_y)
	{
		printf("==%s\n",(cub.map)[i]);
		i++;
	}
	freevars(&cub);
	freemaps(&cub);
}

int		main(int argc, char **argv)
{
	cub3d(argv, argc);
	// while(1)		
	// ;
	return (0);
}
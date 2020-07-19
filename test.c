/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:57:29 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/19 16:20:57 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./cub3d.h"

void num_check_p2(t_struct_num *snum)
{
	if (snum->ltr == 'R')
		(snum->error) = -2;
	else if (snum->ltr == 'F')
		(snum->error) = -3;
	else if (snum->ltr == 'C')
		(snum->error) = -4;
	else
		(snum->error) = -17;
}

int	num_check(t_struct_num *snum, char *line, int *start)
{
	while ((line[snum->i] < '0') || (line[snum->i] > '9'))
	{
		if ((snum->error) != -18 && (line[snum->i] == ' '
		|| (line[snum->i] == ',' && line[(snum->i) + 1] != ',')
		|| line[snum->i] == 'R' || line[snum->i] == 'F'
		|| line[snum->i] == 'C'))
		{
			if (line[snum->i] == 'R' || line[snum->i] == 'F'
			|| line[snum->i] == 'C')
				snum->ltr = line[snum->i];
			if (snum->check > 2 && snum->ltr == 'R')
				(snum->error) = -2;
			(snum->i)++;
		}
		else
		{
			num_check_p2(snum);
			break ;
		}
	}
	*start = snum->i;
	while (((line)[snum->i] >= '0') && ((line)[snum->i] <= '9'))
		(snum->i)++;
	return (snum->error);
}

void	ft_error_c3d(int error)
{
	printf("error = %d\n", error);
	if (error == -1)
		write(1, "ERROR;\tdunno what is fricked\n", 29);
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
		write(1, "ERROR;\tS is fricked\n", 20); //-11
	if (error == -10)
		write(1, "ERROR;\tPath is fricked\n", 23);
	if (error == -11)
		write(1, "ERROR;\tno gucci man\n", 21);
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
	return (error);
}

void	struct_num_init(t_struct_num *snum)
{
	snum->st = 0;
	snum->check = 1;
	snum->i = 0;
	snum->error = 0;
	snum->temp = 0;
	snum->ltr = 0;
}

void	struct_num(char *line, int *adr1, int *adr2, int *adr3)
{
	t_struct_num snum;

	struct_num_init(&snum);
	while (line[snum.i] != '\0')
	{
		if (snum.check > 3)
			snum.error = -18;	/*Error for too many numbers, 3 the max yo*/
		snum.error = num_check(&snum, line, &(snum.st));
		if (snum.error != 0)
			ft_error_c3d(snum.error);
		snum.temp = malloc(((snum.i) - (snum.st)) * sizeof(char) + 1);
		ft_strlcpy(snum.temp, &line[snum.st], ((snum.i) - (snum.st)) + 1);
		if (snum.check == 1)
			snum.error = strcut_num_loopcheck(adr1, snum.error, snum.temp);
		if (snum.check == 2)
			snum.error = strcut_num_loopcheck(adr2, snum.error, snum.temp);
		if (snum.check == 3)
			snum.error = strcut_num_loopcheck(adr3, snum.error, snum.temp);
		free(snum.temp);
		snum.check++;
	}
}

char	*struct_path(t_cub3d *cub, char **line)
{
	int		len;
	char	*temp;

	while ((*line)[(cub->i)] != '.' && (*line)[(cub->i)] != '/'
	&& (*line)[(cub->i)] != '\0')
		(cub->i)++;
	if ((*line)[(cub->i)] == '\0')
		cub->error = -10;
	if (cub->error != 0)
		ft_error_c3d(cub->error);
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
	cub->error = 0;
	cub->i = -1;
	cub->maxstrlen = -1;
	cub->maxrx = 1920;			//add function that actually calculates dis bish
	cub->maxry = 1080;
}

int	ft_checkmapplacement(t_cub3d *cub)
{
	if (cub->rx == -1 || cub->ry == -1 || cub->no == 0 || cub->so == 0 
	|| cub->we == 0 || cub->ea == 0 || cub->s == 0 || cub->fr == -1 
	|| cub->fg == -1 || cub->fb == -1 || cub->cr == -1 || cub->cg == -1 || cub->cb == -1)
	{
		cub->error = -11;
		if (cub->error != 0)
		ft_error_c3d(cub->error);
		return(-1);
	}	
	return (0);
}

int		jumping(char *line, t_cub3d *cub, int ret)
{
	printf("jumping|%d\n\tline=%s\n", cub->cb, line);
	if ((line[(cub->i)] == 'R' && line[(cub->i) + 1] == ' '))
		struct_num(line, &cub->rx, &cub->ry, &cub->ry);
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
		struct_num(line, &cub->fr, &cub->fg, &cub->fb);
	if (line[(cub->i)] == 'C' && line[(cub->i) + 1] == ' ')
		struct_num(line, &cub->cr, &cub->cg, &cub->cb);
	if (line[(cub->i)] == '0' || line[(cub->i)] == '1')
	{
		if(ft_checkmapplacement(cub) == 0)
			ret = read_map(cub, line, ret);
		
	}
		
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
		printf("mapping|%d\n", cub->cb);
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

void	check_if_empty(t_cub3d *cub)
{
	if ((cub->rx < 0 || cub->rx > cub->maxrx)
	|| (cub->ry < 0 || cub->ry > cub->maxry))
		cub->error = -2;
	if (cub->no == 0)
		cub->error = -5;
	if (cub->so == 0)
		cub->error = -6;
	if (cub->we == 0)
		cub->error = -7;
	if (cub->ea == 0)
		cub->error = -8;
	if (cub->s == 0)
		cub->error = -9;
	if ((cub->fr < 0 || cub->fr > 255) || (cub->fg < 0 || cub->fg > 255)
	|| (cub->fb < 0 || cub->fb > 255))
		cub->error = -3;
	if ((cub->cr < 0 || cub->cr > 255) || (cub->cg < 0 || cub->cg > 255)
	|| (cub->cb < 0 || cub->cb > 255))
		cub->error = -4;
}

void	validity(t_cub3d *cub)
{
	check_if_empty(cub);
	if (cub->error != 0)
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


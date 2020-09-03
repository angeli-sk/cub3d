/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cub3d.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:32:35 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 22:07:07 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../get_next_line/get_next_line.h"
#include <fcntl.h>

static void	read_map(t_parse *cub)
{
	int chk;
	int len;

	chk = 0;
	if (cub->temp == 0)
		chk = 1;
	cub->temp = ft_strjoin_c3d(cub, cub->temp, cub->line);
	cub->max_y++;
}

int			ft_checkmapplacement(t_parse *cub)
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

static void	parsing(t_parse *cub)
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
}

static void	readfile(t_parse *cub)
{
	int ret;

	ret = 1;
	while (ret == 1)
	{
		(cub->i) = 0;
		ret = get_next_line(cub->fd, &(cub->line));
		cub->ret = ret;
		while ((cub->line)[cub->i] == ' ')
			(cub->i)++;
		parsing(cub);
		if ((cub->line)[(cub->i)] == '\0' && cub->beginmap == 1)
			cub->beginmap = 2;
		if ((cub->line)[(cub->i)] != '\0' && cub->beginmap == 2)
			cub->error = invalid_map;
		if (ret == 1)
			free((cub->line));
	}
	if (cub->error == invalid_map)
		ft_exit_c3d(cub, "Your map is fricked", 19);
	if (cub->error == invalid_char)
		ft_exit_c3d(cub, "There's sum garbo man, clean it", 31);
	cub->map = ft_split_c3d(cub, cub->temp, '\n');
	cub->mapcopy = ft_split_c3d(cub, cub->temp, '\n');
}

void		parser(t_parse *cub, char **argv, int argc)
{
	if (argc < 2 || argc > 3)
		ft_exit_c3d(cub, "Not the right amount of arguments", 33);
	struct_init(cub);
	cub->fd = open(argv[1], O_RDONLY);
	if (cub->fd < 0)
		ft_exit_c3d(cub, "Open failed; lemao defrick, how??", 33);
	readfile(cub);
	validity(cub);
	cub->f_color = 65536 * cub->fr + 256 * cub->fg + cub->fb;
	cub->c_color = 65536 * cub->cr + 256 * cub->cg + cub->cb;
}

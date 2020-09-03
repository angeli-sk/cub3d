/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:40:21 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/03 20:31:59 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdio.h>

void	check_if_s_empty(t_parse *cub)
{
	if ((cub->line)[0] == 'N' && (cub->line)[1] == 'O'
			&& cub->no != 0)
		ft_exit_c3d(cub, "NO is fricked", 13);
	else if ((cub->line)[0] == 'S' && (cub->line)[1] == 'O'
			&& cub->so != 0)
		ft_exit_c3d(cub, "SO is fricked", 13);
	else if ((cub->line)[0] == 'W' && (cub->line)[1] == 'E'
			&& cub->we != 0)
		ft_exit_c3d(cub, "WE is fricked", 13);
	else if ((cub->line)[0] == 'E' && (cub->line)[1] == 'A'
			&& cub->ea != 0)
		ft_exit_c3d(cub, "EA is fricked", 13);
	else if ((cub->line)[0] == 'S' && (cub->line)[1] == ' '
			&& cub->s != 0)
		ft_exit_c3d(cub, "S is fricked", 12);
	else
		return ;
}

char	*struct_path(t_parse *cub)
{
	int		len;
	char	*temp;
	int		tempi;

	len = 0;
	tempi = 0;
	(cub->i) = (cub->i) + 2;
	while ((cub->line)[(cub->i)] == ' ')
		(cub->i)++;
	check_if_s_empty(cub);
	tempi = cub->i;
	while ((cub->line)[tempi] != '\0')
		tempi++;
	len = tempi - cub->i;
	temp = malloc(sizeof(char) * (len + 1));
	if (temp == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck", 21);
	ft_strlcpy(temp, &((cub->line)[(cub->i)]), len + 1);
	return (temp);
}

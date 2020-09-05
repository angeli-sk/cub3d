/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_num_parse.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 22:38:49 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 17:50:03 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	num_check_aswell(t_parse *cub)
{
	if (cub->num_ltr == 'R')
		ft_exit_c3d(cub, "R is fricked", 12);
	else if (cub->num_ltr == 'F')
		ft_exit_c3d(cub, "F is fricked", 12);
	else if (cub->num_ltr == 'C')
		ft_exit_c3d(cub, "C is fricked", 12);
	else
		ft_exit_c3d(cub, "? is fricked", 12);
}

void	ft_check_if_numcorrect(t_parse *cub)
{
	int tempi;

	tempi = 0;
	while ((cub->num_ltr == 'R' && (cub->line)[tempi] != '\0'))
	{
		if ((cub->line)[tempi] == ',')
			ft_exit_c3d(cub, "R is fricked", 12);
		tempi++;
	}
	tempi = cub->num_st;
	while (((cub->num_ltr == 'F' || cub->num_ltr == 'C') &&
			(cub->line)[tempi] != '\0'))
	{
		if (ft_isspace((cub->line)[tempi]) == 1)
		{
			if (cub->num_ltr == 'F')
				ft_exit_c3d(cub, "F is fricked", 12);
			else
				ft_exit_c3d(cub, "C is fricked", 12);
		}
		tempi++;
	}
}

void	num_check_also(t_parse *cub)
{
	if ((cub->line)[cub->num_i] == 'R' || (cub->line)[cub->num_i] == 'F'
	|| (cub->line)[cub->num_i] == 'C')
	{
		cub->num_ltr = (cub->line)[cub->num_i];
		if (cub->num_ltr == 'F' && cub->f == 0)
			cub->f = 1;
		else if (cub->num_ltr == 'F' && cub->f == 1)
			ft_exit_c3d(cub, "F is fricked", 12);
		if (cub->num_ltr == 'C' && cub->c == 0)
			cub->c = 1;
		else if (cub->num_ltr == 'C' && cub->c == 1)
			ft_exit_c3d(cub, "C is fricked", 12);
		if (cub->num_ltr == 'R' && cub->r == 0)
			cub->r = 1;
		else if (cub->num_ltr == 'R' && cub->r == 1)
			ft_exit_c3d(cub, "R is fricked", 12);
	}
	if (cub->num_check > 2 && cub->num_ltr == 'R')
		ft_exit_c3d(cub, "R is fricked", 12);
	(cub->num_i)++;
}

void	num_check(t_parse *cub)
{
	while (((cub->line)[cub->num_i] < '0') || ((cub->line)[cub->num_i] > '9'))
	{
		if ((cub->num_error) != too_many_nums && ((cub->line)[cub->num_i] == ' '
		|| ((cub->line)[cub->num_i] == ',' &&
			(cub->line)[cub->num_i + 1] != ',')
		|| (cub->line)[cub->num_i] == 'R' || (cub->line)[cub->num_i] == 'F'
		|| (cub->line)[cub->num_i] == 'C'))
			num_check_also(cub);
		else
		{
			num_check_aswell(cub);
			break ;
		}
	}
	cub->num_st = cub->num_i;
	while ((((cub->line))[cub->num_i] >= '0') &&
			(((cub->line))[cub->num_i] <= '9'))
		(cub->num_i)++;
	ft_check_if_numcorrect(cub);
}

void	struct_num(t_parse *cub, int *adr1, int *adr2, int *adr3)
{
	cub->num_st = 0;
	cub->num_check = 1;
	cub->num_i = 0;
	cub->num_error = 0;
	cub->num_ltr = 0;
	while ((cub->line)[cub->num_i] != '\0')
	{
		if (cub->num_check > 3)
			cub->num_error = too_many_nums;
		num_check(cub);
		cub->num_temp = ft_calloc(((cub->num_i
			- cub->num_st) + 1), sizeof(char));
		if (cub->num_temp == 0)
			ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
		ft_strlcpy(cub->num_temp, &(cub->line)[cub->num_st],
			((cub->num_i) - (cub->num_st)) + 1);
		if (cub->num_check == 1)
			*adr1 = ft_atoi(cub->num_temp);
		if (cub->num_check == 2)
			*adr2 = ft_atoi(cub->num_temp);
		if (cub->num_check == 3)
			*adr3 = ft_atoi(cub->num_temp);
		free(cub->num_temp);
		cub->num_check++;
	}
}

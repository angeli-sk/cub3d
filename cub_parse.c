#include "./cub3d.h"
# include "./libft/libft.h"
#include <stdlib.h>


void		check_if_s_empty(t_parse *cub) //parse
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

char	*struct_path(t_parse *cub) //path parse
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
	while((cub->line)[tempi] != '\0')
		tempi++;
	len = ft_strlen(&(cub->line)[(cub->i)]);
	temp = malloc((sizeof(char) * len) + 1);
	if (temp == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	temp[len] = '\0';
	ft_strlcpy(temp, &((cub->line)[(cub->i)]), len + 1);
	return (temp);
}
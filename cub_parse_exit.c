#include <unistd.h>
#include <stdlib.h>
#include "./cub3d.h"
#include "./get_next_line/get_next_line.h"

void	freemaps(t_parse *cub) //free
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

void	freevars(t_parse *cub) //free
{
	if (cub->line)
		free((cub->line));
    if (cub->num_temp)
		free((cub->num_temp));
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->s)
		free(cub->s);
	if (cub->temp)
	    free((cub->temp));
}

void	ft_write_error(char *s, int len) //free error
{
	write (1, "ERROR\n", 6);
	write (1, s, len);
	write(1, "\n", 1);
}

void	ft_exit_c3d(t_parse *cub, char *s, int len) // error
{
	write (1, "ERROR\n", 6);
	write (1, s, len);
	write(1, "\n", 1);
    // while(cub->ret != 0)
    // {printf("test");
    //     cub->ret = get_next_line(cub->fd, &(cub->line));
    //     if (cub->ret == 1)
	// 		free((cub->line));
    // }
	freevars(cub);
	if (cub->beginmap != 0)
		freemaps(cub);
	close(cub->fd);
	exit(1);
}
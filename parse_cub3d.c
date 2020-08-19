#include "./cub3d.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>

void		read_map(t_parse *cub) //parse
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

int	ft_checkmapplacement(t_parse *cub) //error
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

void		parsing(t_parse *cub) //parse
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

void	readfile(t_parse *cub, char *path) // read
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
        cub->ret = ret;
		while ((cub->line)[cub->i] == ' ')
			(cub->i)++;
		parsing(cub);
		if (ret == 1)
		{
            free((cub->line));
            cub->line = NULL;
        }	
	}
	//free((cub->line));
    //cub->line = NULL;
	if (cub->error == invalid_map)
		ft_exit_c3d(cub, "Your map is fricked", 19);
	if (cub->error == invalid_char)
		ft_exit_c3d(cub, "There's sum garbo man, clean it", 31);
	cub->map = ft_split_c3d(cub, cub->temp, '\n');
	cub->mapcopy = ft_split_c3d(cub, cub->temp, '\n');
	//close(fd);
}

void	parser(t_parse *cub, char **argv, int argc) //cub
{
	if (argc < 2 || argc > 3)
		ft_exit_c3d(cub, "Not the right amount of arguments", 33);
	struct_init(cub);
	readfile(cub, argv[1]);//make error function for this too many args too litlle etc
	printf("lemao\n");
	printf("RX=%d\nRY=%d\nNO=%s\nSO=%s\nWE=%s\nEA=%s\nS=%s\n", cub->rx, cub->ry, cub->no, cub->so, cub->we, cub->ea, cub->s);
	printf("Fr=%i\nFg=%i\nFb=%i\nC=%i\nCg=%i\nCb=%i\n",cub->fr, cub->fg, cub->fb, cub->cr, cub->cg, cub->cb);
	validity(cub);
	int i = 0;
	while (i < cub->max_y)
	{
		printf("==%s\n",(cub->mapcopy)[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < cub->max_y)
	{
		printf("==%s\n",(cub->map)[i]);
		i++;
	}
	
}

void	cub3d(int argc, char **argv)
{
	t_parse cub;
	parser(&cub, argv, argc);
	ft_mlx(&cub, argv, argc);
	//mlx_loop_hook(cub.vars.mlx,	render_next_frame(cub), cub.vars.mlx);
	freevars(&cub);
	freemaps(&cub);
}

int		main(int argc, char **argv)
{
	cub3d(argc, argv);
	// while(1)		
	// ;
	return (0);
}
#include "./cub3d.h"
#include "./libft/libft.h"

void	struct_num_init(t_parse *cub) //initialize
{
	cub->num_st = 0;
	cub->num_check = 1;
	cub->num_i = 0;
	cub->num_error = 0;
	//cub->num_temp = 0;
	cub->num_ltr = 0;
}

void	struct_init(t_parse *cub) //init
{
	ft_bzero(cub, sizeof(t_parse));
	ft_bzero(&cub->img, sizeof(t_parse));
	ft_bzero(&cub->vars, sizeof(t_parse));
	ft_bzero(&cub->arr, sizeof(t_parse));
	ft_bzero(&cub->sprite, sizeof(t_jonas));
	int i;
	i = 0;
	while(i < 5)
	{
		ft_bzero(&cub->tex[i], sizeof(t_parse));
		i++;
	}
	cub->rx = -1;
	cub->ry = -1;
	// cub->no = 0;
	// cub->so = 0;
	// cub->we = 0;
	// cub->ea = 0;
	// cub->s = 0;
	cub->fr = -1;
	cub->fr = -1;
	cub->fb = -1;
	cub->cr = -1;
	cub->cg = -1;
	cub->cb = -1;
	// cub->temp = 0;
	// cub->map = 0;
	// cub->mapcopy = 0;
	// cub->error = 0;
	// cub->beginmap = 0;
	cub->i = -1;
	cub->maxstrlen = -1;
	cub->maxrx = 1920;			//add function that actually calculates dis bish
	cub->maxry = 1080;
	// cub->players = 0;
	// cub->objects = 0;
	// cub->startx = 0;
	// cub->starty = 0;
	// cub->max_y = 0;
	// cub->line = NULL;
	// cub->r = 0;
	// cub->f = 0;
	// cub->c = 0;
	// cub->fd = 0;
    // cub->ret = 0;
    // cub->num_st = 0;
	cub->num_check = 1;
// 	cub->num_i = 0;
// 	cub->num_error = 0;
// 	cub->num_temp = NULL;
// 	cub->num_ltr = 0;
	cub->ltr = 0;
}
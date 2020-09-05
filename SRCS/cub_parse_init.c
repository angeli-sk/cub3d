/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub_parse_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <akramp@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 21:34:52 by akramp        #+#    #+#                 */
/*   Updated: 2020/09/05 15:13:53 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"

void		get_tex(t_parse *cub)
{
	int		i;
	char	*arr[5];

	i = 0;
	arr[0] = cub->no;
	arr[1] = cub->so;
	arr[2] = cub->we;
	arr[3] = cub->ea;
	arr[4] = cub->s;
	file_checkor(cub);
	while (i < 5)
	{
		cub->tex[i].img = mlx_png_file_to_image(cub->vars.mlx, \
		arr[i], &cub->tex[i].x, &cub->tex[i].y);
		if (cub->tex[i].img == NULL)
			ft_exit_c3d(cub, "Incorrect png file", 18);
		cub->tex[i].addr = mlx_get_data_addr(cub->tex[i].img, \
		&cub->tex[i].bits_per_pixel, &cub->tex[i].line_length,
		&cub->tex[i].endian);
		i++;
	}
}

static void	struct_bzero(t_parse *cub)
{
	int i;

	ft_bzero(cub, sizeof(t_parse));
	ft_bzero(&cub->img, sizeof(t_parse));
	ft_bzero(&cub->vars, sizeof(t_parse));
	ft_bzero(&cub->arr, sizeof(t_parse));
	ft_bzero(&cub->sprite, sizeof(t_sprite));
	i = 0;
	while (i < 6)
	{
		ft_bzero(&cub->vars.walksies[i], sizeof(t_array));
		i++;
	}
	i = 0;
	while (i < 5)
	{
		ft_bzero(&cub->tex[i], sizeof(t_parse));
		i++;
	}
}

static void	view_init(t_parse *cub)
{
	if (cub->ltr == 'S')
	{
		cub->vars.dir_y = 1.0;
		cub->vars.plane_x = -0.66;
	}
	if (cub->ltr == 'W')
	{
		cub->vars.dir_x = -1.0;
		cub->vars.plane_y = -0.66;
	}
	if (cub->ltr == 'N')
	{
		cub->vars.dir_y = -1.0;
		cub->vars.plane_x = 0.66;
	}
	if (cub->ltr == 'E')
	{
		cub->vars.dir_x = 1.0;
		cub->vars.plane_y = 0.66;
	}
}

void		mlx_vars_init(t_parse *cub)
{
	cub->vars.spd = 0.1;
	cub->vars.rot_speed = 0.05;
	cub->vars.olddir_x = 0;
	cub->vars.oldplane_x = 0;
	cub->vars.colorwall = 255;
	cub->vars.cam_x = 0.0;
	cub->vars.ray_x = 0.0;
	cub->vars.ray_y = 0.0;
	cub->vars.x = 0;
	cub->vars.h = cub->ry;
	cub->vars.w = cub->rx;
	cub->vars.pos_x = (double)cub->startx + 0.5;
	cub->vars.pos_y = (double)cub->starty + 0.5;
	cub->vars.z_buff = ft_calloc(cub->rx, sizeof(double));
	if (cub->vars.z_buff == 0)
		ft_exit_c3d(cub, "Malloc failed, u suck\n", 22);
	cub->sprite_order = ft_calloc(cub->objects, sizeof(int));
	view_init(cub);
}

void		struct_init(t_parse *cub)
{
	struct_bzero(cub);
	cub->rx = -1;
	cub->ry = -1;
	cub->fr = -1;
	cub->fr = -1;
	cub->fb = -1;
	cub->cr = -1;
	cub->cg = -1;
	cub->cb = -1;
	cub->i = -1;
	cub->maxstrlen = -1;
	mlx_get_screen_size(cub->vars.mlx, &cub->maxrx, &cub->maxry);
	cub->num_check = 1;
}

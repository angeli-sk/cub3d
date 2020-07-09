/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 16:40:24 by akramp        #+#    #+#                 */
/*   Updated: 2020/07/09 16:24:13 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <sys/_types/_size_t.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

typedef struct	s_cub3d
{
	int		rx;
	int		ry;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
	char	*temp;
	char	**map;
	int		error;
	int		maxstrlen;
	int		i;
}				t_cub3d;

typedef struct s_mapinfo
{
	char wall;
	char item;
	char emptyspace;
	char player;
}				t_mapinfo;

void cub3d(void);

//libft
char	*ft_strjoin_c3d(t_cub3d *cub, char const *s1, char const *s2);
t_cub3d *cub;

#endif
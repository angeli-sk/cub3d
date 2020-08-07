/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 16:40:24 by akramp        #+#    #+#                 */
/*   Updated: 2020/08/07 19:48:10 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
#include <stdio.h>


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
	char	**mapcopy;
	int		beginmap;
	int		error;
	int		maxstrlen;
	int		i;
	int		maxrx;
	int		maxry;
	int		players;
	int		objects;
	int		startx;
	int		starty;
}				t_cub3d;

typedef struct s_splitty
{
	int		y;
	int		len;
	char	c;
	int		maxlen;
}				t_splitty;

typedef struct	s_struct_num
{
	int		st;
	int		check;
	char	*temp;
	int		i;
	char	ltr;
	int		error;
}				t_struct_num;

typedef struct	s_mapinfo
{
	char wall;
	char item;
	char emptyspace;
	char player;
}				t_mapinfo;

void cub3d(char **argv, int argc);

/*libft*/
char	*ft_strjoin_c3d(t_cub3d *cub, char const *s1, char const *s2);
char		**ft_split_c3d(t_cub3d *cub, char const *s, char c);
void	*ft_calloc_mlx(size_t count, size_t size);
void	ft_bzero_mlx(void *s, size_t n);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 16:40:24 by akramp        #+#    #+#                 */
/*   Updated: 2020/06/26 17:22:28 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <sys/_types/_size_t.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

typedef struct	s_cub3d
{
	int RX;
	int RY;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *S;
	int FR;
	int FG;
	int FB;
	int CR;
	int CG;
	int CB;
	char *temp;
	char **map;
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
char	*ft_strjoin_c3d(char const *s1, char const *s2);

#endif
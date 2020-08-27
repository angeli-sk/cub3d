/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 14:09:11 by akramp         #+#    #+#                */
/*   Updated: 2019/12/30 13:44:17 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int			get_next_line(int fd, char **line);
int			ft_strlen_gnl(const char *str);
void		*ft_memcpy_gnl(void *dst, const void *src, int n);
char		*ft_strjoin_gnl(char *s1, char *s2);
int			ft_strlcpy_gnl(char *dst, const char *src, int dstsize);
char		*ft_fill(char *str, char const *s1, char const *s2);
int			g_n_l_read(char **str, char **buffer, int fd, int *i);
void		g_n_l_eol(int ret, char **str, int *i, char **buffer);
int			ft_free(char **str, char **buffer, int check);
int			empty_s(char **str);

#endif

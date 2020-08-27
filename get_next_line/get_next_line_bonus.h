/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 14:09:11 by akramp         #+#    #+#                */
/*   Updated: 2019/12/30 13:57:19 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int			ft_strlcpy(char *dst, const char *src, int dstsize);
int			g_n_l_read(char **str, char **buffer, int fd, int *i);
int			g_n_l_eol(int ret, char **str, int *i, char **buffer);
int			empty_s(char **str);
int			get_next_line(int fd, char **line);
int			ft_strlen(const char *str);
void		*ft_memcpy(void *dst, const void *src, int n);
char		*ft_fill(char *str, char const *s1, char const *s2);
int			ft_free(char **str, char **buffer, int check);
char		*ft_strjoin(char *s1, char *s2);

#endif

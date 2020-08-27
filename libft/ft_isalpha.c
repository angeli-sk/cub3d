/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akramp <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:27:42 by akramp         #+#    #+#                */
/*   Updated: 2019/11/17 13:14:46 by akramp        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_upper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

static int	ft_is_lower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}

int			ft_isalpha(int c)
{
	if (ft_is_upper(c) != 0 || ft_is_lower(c) != 0)
		return (1);
	else
		return (0);
}

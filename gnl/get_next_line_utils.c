/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:56:41 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/16 12:12:09 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_copy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

void	ft_strjoin_gnl(char *s1, char *s2)
{
	int	iter_1;
	int	iter_2;

	iter_1 = ft_strlen_gnl(s1);
	iter_2 = 0;
	while (s2[iter_2])
	{
		s1[iter_1] = s2[iter_2];
		iter_1++;
		iter_2++;
	}
	s1[iter_1] = 0;
}

int	ft_strlen_gnl(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i])
		i++;
	if ((char)c && !s[i])
		return (0);
	return ((char *)&s[i]);
}

char	*ft_trunc(char *concat)
{
	int	iter;

	iter = 0;
	if (concat && ft_strchr_gnl(concat, '\n'))
	{
		while (concat[iter] != '\n')
			iter++;
		iter += 1;
		concat[iter] = 0;
	}
	return (concat);
}

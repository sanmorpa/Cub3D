/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 08:52:46 by samoreno          #+#    #+#             */
/*   Updated: 2022/09/07 09:56:06 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_free_twice(char *str_1, char *str_2)
{
	free(str_1);
	free(str_2);
	return (NULL);
}

static char	*ft_fill(char *temp, int buff, int *fd)
{
	char	*ptr_concat;
	char	*concat;
	int		byte_seen;

	concat = malloc(sizeof(char) * (ft_strlen_gnl(temp) + buff + 1));
	if (!concat)
	{
		free(temp);
		return (NULL);
	}
	concat[0] = 0;
	ptr_concat = concat;
	ft_strjoin_gnl(concat, temp);
	concat += ft_strlen_gnl(concat);
	byte_seen = read(*fd, concat, buff);
	if (byte_seen < 0)
		return (ft_free_twice(temp, concat));
	if (byte_seen == 0)
		*fd = -2;
	else
		concat += byte_seen;
	*concat = 0;
	free(temp);
	return (ptr_concat);
}

static char	*ft_rest(char *concat, char **rest)
{
	if (!*rest)
		*rest = malloc(sizeof(char) * (ft_strlen_gnl(concat) + 1));
	if (!*rest)
	{
		free(concat);
		return (NULL);
	}
	else
		ft_copy(*rest, (ft_strchr_gnl(concat, '\n') + 1));
	return (*rest);
}

static char	*ft_decision(char **rest, int buff, int *fd)
{
	char	*concat;

	if (*rest)
	{
		concat = *rest;
		*rest = 0;
	}
	else
	{
		concat = malloc(buff + 1);
		if (!concat)
			return (NULL);
		concat[0] = 0;
	}
	while (!ft_strchr_gnl(concat, '\n') && *fd != -2)
	{
		concat = ft_fill(concat, buff, fd);
		if (!concat || (concat && concat[0] == 0))
		{
			if (concat)
				free(concat);
			return (NULL);
		}
	}
	return (concat);
}

char	*get_next_line(int fd)
{
	char		*concatenated;
	static char	*rest[4096];
	int			buffer_size;

	buffer_size = 1;
	if (fd < 0 || buffer_size <= 0)
		return (NULL);
	concatenated = ft_decision(&rest[fd], buffer_size, &fd);
	if (!concatenated)
		return (NULL);
	if (ft_strchr_gnl(concatenated, '\n'))
	{
		ft_rest(concatenated, &rest[fd]);
		if (!rest[fd])
			return (NULL);
	}
	concatenated = ft_trunc(concatenated);
	return (concatenated);
}

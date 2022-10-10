/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <samoreno@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:39:45 by samoreno          #+#    #+#             */
/*   Updated: 2022/10/03 12:40:21 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	comma_together(char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (comma == 1)
				return (1);
			comma = 1;
		}
		else
			comma = 0;
		i++;
	}
	return (0);
}

static int	digit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_colors(char **color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (digit_str(color[i]) == 0)
			return (1);
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	parse_fc(char *c, char *f)
{
	char	**split_c;
	char	**split_f;
	int		ret;

	if (comma_together(c) == 1 || comma_together(f) == 1)
		return (1);
	split_c = ft_split(c, ',');
	split_f = ft_split(f, ',');
	if (!split_c || !split_f)
	{
		if (split_c)
			ft_free(split_c, count_split(split_c));
		return (1);
	}
	if (check_colors(split_c) == 1 || check_colors(split_f) == 1)
		ret = 1;
	else
		ret = 0;
	ft_free(split_c, count_split(split_c));
	ft_free(split_f, count_split(split_f));
	return (ret);
}

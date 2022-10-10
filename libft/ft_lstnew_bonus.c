/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:59:23 by samoreno          #+#    #+#             */
/*   Updated: 2021/11/12 09:59:24 by samoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_cont;

	new_cont = malloc(sizeof(t_list));
	if (!new_cont)
		return (NULL);
	(*new_cont).content = content;
	(*new_cont).next = NULL;
	return (new_cont);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envar_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:37:07 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:37:16 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_envar_position(t_envar *envar, char *str)
{
	t_envar	*tmp;
	int		i;

	i = 0;
	tmp = envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str))
		{
			i++;
			return (i);
		}
		i++;
		tmp = tmp->next;
	}
	return (0);
}

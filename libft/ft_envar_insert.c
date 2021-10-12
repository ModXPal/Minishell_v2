/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envar_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:41:36 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:41:59 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	envar_insert(t_envar**envar, t_envar *new, int pos)
{
	t_envar	*start;
	t_envar	*tmp;
	int		i;

	start = *envar;
	i = 0;
	if (pos < 2 || pos > ft_envarsize(*envar))
	{
		free(new);
		return (0);
	}
	while (*envar && ++i < pos - 1)
	{
		*envar = (*envar)->next;
	}
	tmp = (*envar)->next;
	(*envar)->next = new;
	new->next = tmp;
	*envar = start;
	return (1);
}

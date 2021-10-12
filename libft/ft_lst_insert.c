/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:40:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:41:26 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	list_insert(t_list **list, t_list *new, int pos)
{
	t_list	*start;
	t_list	*tmp;
	int		i;

	start = *list;
	i = 0;
	if (pos < 2 || pos > ft_lstsize(*list))
	{
		free(new);
		return (0);
	}
	while (*list && ++i < pos - 1)
	{
		*list = (*list)->next;
	}
	tmp = (*list)->next;
	(*list)->next = new;
	new->next = tmp;
	*list = start;
	return (1);
}

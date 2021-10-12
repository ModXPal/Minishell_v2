/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:42:15 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:42:24 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	list_remove(t_list **list, int pos)
{
	t_list	*start;
	t_list	*tmp;
	int		i;

	start = *list;
	i = 0;
	if (pos < 1 || pos > ft_lstsize(*list))
		return (0);
	while (*list && ++i < pos - 1)
	{
		*list = (*list)->next;
	}
	if (i == 1)
		*list = (*list)->next;
	else
	{
		tmp = (*list)->next;
		if ((*list)->next->next)
			(*list)->next = (*list)->next->next;
		else
			(*list)->next = NULL;
		free(tmp);
		*list = start;
	}
	return (1);
}

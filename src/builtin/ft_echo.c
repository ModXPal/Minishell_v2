/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:29:41 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/14 14:34:42 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_dash_n(t_list *list)
{
	int	i;

	i = 0;
	if (!list->next)
		return (0);
	if (list->next->content[i] == '-')
	{
		i++;
		while (list->next->content[i] == 'n')
		{
			if (list->next->content[i + 1] == '\0'
				|| list->next->content[i + 1] == ' ')
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	ft_echo(t_var *var)
{
	t_list	*start;
	int		i;
	int		ret;

	i = -1;
	start = var->list;
	ret = is_dash_n(start);
	if (ret == TRUE)
		start = start->next;
	while (start)
	{
		printf("%s", start->content);
		if (start->next)
			printf(" ");
		start = start->next;
	}
	if (ret == FALSE)
		printf("\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envar_find_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:36:11 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/12 14:36:35 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_envar_find_content(t_envar *tmp, char *str)
{
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str))
		{
			str = tmp->content;
			return (str);
		}
		tmp = tmp->next;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envar_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:49:27 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 10:38:45 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_envar	*ft_envar_new(char *name, char *content)
{
	t_envar	*new_list;

	new_list = (t_envar *)malloc(sizeof(t_envar));
	if (!new_list)
		return (NULL);
	new_list->name = name;
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

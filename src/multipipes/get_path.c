/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:49:25 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/04 11:36:47 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

void	add_slash(t_pvar *pvar)
{
	int		i;
	char	*to_free;

	i = -1;
	while (pvar->path[++i])
	{
		to_free = pvar->path[i];
		pvar->path[i] = ft_strjoin(pvar->path[i], "/");
		free(to_free);
	}
}

char	**get_binaries_path(t_var *var)
{
	char	*path;

	path = get_valid_envar(var, "PATH", 0);
	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}

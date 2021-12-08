/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:49:25 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/06 10:32:24 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

void	add_slash(t_pvar *pvar)
{
	int		i;
	char	*to_free;

	i = -1;
	if (pvar->path == NULL)
		return ;
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
	char	**split_path;

	path = get_valid_envar(var, "PATH", 0);
	if (path == NULL)
		return (NULL);
	split_path = ft_split(path, ':');
	if (path)
		free (path);
	return (split_path);
}

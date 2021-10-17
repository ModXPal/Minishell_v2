/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_parent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:34:45 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/15 17:20:50 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_parent(t_var *var, int parent)
{
	int	i;

	i = -1;
	(void) parent;
	while (++i < var->pipes->size_cmd_pipes)
	{
		if (i != var->pipes->size_cmd_pipes)
			close(var->pipes->tab_pipes[i][0]);
		if (i != 0)
			close(var->pipes->tab_pipes[i][1]);
	}
	i = -1;
	while (++i < var->pipes->size_cmd_pipes)
		waitpid(parent, 0, 0);
}
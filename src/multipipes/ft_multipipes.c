/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multipipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:59:45 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/19 16:43:39 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_creation(t_var *var)
{
	int	i;

	i = -1;
	var->pipes->tab_pipes = malloc(sizeof(int *) * (var->pipes->size_cmd_pipes + 1));
	if (var->pipes->tab_pipes == 0)
		return ((void)0);
	while (++i < var->pipes->size_cmd_pipes + 1)
		var->pipes->tab_pipes[i] = malloc(sizeof(int) * 2);
	i = -1;
	while (++i < var->pipes->size_cmd_pipes + 1)
	{
		if (pipe(var->pipes->tab_pipes[i]) == -1)
		{
			write(2, "Error\n", 7);
		}
	}
}

int	child_parent_creation(t_var *var)
{
	int parent;
	
	parent = 0;
	var->pipes->i = 0;
	while (var->pipes->i < var->pipes->size_cmd_pipes)
	{
		parent = fork();
		if (parent == 0)
		{
			parsing_child(var);
		}
		var->pipes->i++;
	}
	return (parent);
}

int	fd_creation(t_var *var)
{
	var->pipes->fd[0] = open("test.txt", O_RDONLY);
	var->pipes->fd[1] = open("outfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if ((var->pipes->fd[0] < 0) || (var->pipes->fd[1] < 0))
	{
		if (var->pipes->fd[0] < 0)
			ft_putendl_fd("Permission denied argv[1]", 2);
		if (var->pipes->fd[1] < 0)
			ft_putendl_fd("Permission denied", 2);
	}
	return (0);
}

int	ft_multipipes(t_var *var)
{
	int parent;
	// if (var->pipe == 1)
	// {
	// }
	parent = 0;
	var->pipes->tab_pipes = 0;
	fd_creation(var);
	pipe_creation(var);
	parent = child_parent_creation(var);
	parsing_parent(var, parent);
	return (0);
}


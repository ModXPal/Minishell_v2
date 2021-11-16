/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:24 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 11:57:26 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

void	close_fd(t_var *var)
{
	if (var->input->IN_FD > 0)
		close(var->input->IN_FD);
	if (var->input->OUT_FD > 0)
		close(var->input->OUT_FD);
}

int	close_pipes(t_pvar *pvar, int **pipefd)
{
	int	j;

	j = -1;
	while (++j < pvar->cmd_nb + 1)
	{
		if (close(pipefd[j][0]) == -1)
		{
			perror("Failed to close pipe");
			return (0);
		}
		if (close(pipefd[j][1]) == -1)
		{
			perror("Failed to close pipe");
			return (0);
		}
	}
	return (1);
}

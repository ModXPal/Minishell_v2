/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:24 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/03 15:06:14 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

void	close_fd(t_var *var)
{
	if (var->input == NULL)
		return ;
	if (var->input->in_fd > 0)
		close(var->input->in_fd);
	if (var->input->out_fd > 0)
		close(var->input->out_fd);
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

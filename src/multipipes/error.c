/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:30 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/03 11:32:18 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	cmd_not_found(t_var *var)
{
	write (2, "minishell: ", 11);
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": command not found\n", 20);
	g_exit_status = 127;
	return (0);
}

int	no_such_file(t_var *var)
{
	write (2, "minishell: ", 11);
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": no such file or directory\n", 28);
	g_exit_status = 127;
	return (0);
}

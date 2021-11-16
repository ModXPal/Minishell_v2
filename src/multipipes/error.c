/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:57:30 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/16 11:57:31 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multipipes.h"

int	cmd_not_found(t_var *var)
{
	write (2, "minishell: ", 11);
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": command not found\n", 20);
	EXIT_STATUS = 127;
	return (0);
}

int	no_such_file(t_var *var)
{
	write (2, "minishell: ", 11);
	write (2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": no such file or directory\n", 28);
	EXIT_STATUS = 127;
	return (0);
}

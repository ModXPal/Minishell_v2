/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:48:37 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/02 12:31:22 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	errors_chdir_handling(int dir, t_var *var)
{
	if (dir < 0)
	{
		write (2, "minishell: ", 11);
		write(2, var->input->cmd, ft_strlen(var->input->cmd));
		write (2, ": ", 2);
		write(2, var->input->args[1], ft_strlen(var->input->args[1]));
		write (2, ": ", 2);
		perror("");
		return (1);
	}
	return (0);
}

char	*cd_str_and_path_not_set(t_var *var)
{
	char	*str;
	t_envar	*tmp2;

	tmp2 = var->envar;
	str = NULL;
	str = ft_envar_find_content(tmp2, "HOME");
	if (str == 0)
	{
		write(2, "minishell: cd:", 14);
		ft_putendl_fd(" HOME not set", 2);
		return (0);
	}
	return (str);
}

void	cd_error_message_too_many_arguments(t_var *var)
{
	write (2, "minishell: ", 11);
	write(2, var->input->cmd, ft_strlen(var->input->cmd));
	write (2, ": ", 2);
	write(2, var->input->args[1], ft_strlen(var->input->args[1]));
	write (2, ": too many arguments\n", 21);
}

int	check_if_pwd_exist(t_var *var)
{
	t_envar	*tmp;

	tmp = var->envar;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD"))
		{
			var->pwd_exist = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	cd_swap_with_no_args(t_var *var, t_envar *tmp, char *current_path)
{
	char	*to_free;

	(void) var;
	to_free = 0;
	if (tmp)
	{
		to_free = tmp->content;
		tmp->content = current_path;
		if (to_free && var->pwd_exist == 0)
		{
			free(to_free);
			to_free = NULL;
		}
	}
	else
	{
		if (current_path)
		{
			free(current_path);
			current_path = NULL;
		}
	}
	return (0);
}

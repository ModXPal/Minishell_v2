/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:48:37 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/03 11:28:26 by                  ###   ########.fr       */
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

int	cd_swap_with_no_args(t_var *var, t_envar *tmp, char *current_path)
{
	char	*to_free;

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

int	if_error_no_pwd_oldpwd(t_var *var)
{
	if (var->pwd_exist == 0 || var->pwd_exist == 0)
	{
		if (var->pwd_exist == 0)
		{
			write (2, "minishell: ", 11);
			write (2, "PWD doesn't exist\n", 18);
		}
		if (var->oldpwd_exist == 0)
		{
			write (2, "minishell: ", 11);
			write (2, "OLDPWD doesn't exist\n", 21);
		}
		EXIT_STATUS = 1;
		return (EXIT_STATUS);
	}
	return (0);
}

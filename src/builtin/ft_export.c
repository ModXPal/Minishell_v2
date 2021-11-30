/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:45:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/26 11:32:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_assignement(t_var *var, int i, int already_exist_export,
						int already_exist_env)
{
	(void) already_exist_env;
	i = 0;
	i = export_env_reassigned_check(var, var->env_name, var->env_content);
	if (var->equal_env == 1 && i != -1)
		export_env_insert(var, var->env_name, var->env_content);
	if (export_export_reassigned_check(var, var->export_name,
			var->export_content, already_exist_export) != -1)
		cmd_export_insert(var, var->export_name, var->export_content);
	return (0);
}

int	export_name_content(t_var *var, char *args)
{
	int		i;
	int		j;
	int		already_exist_export;
	int		already_exist_env;

	i = 0;
	j = 0;
	var->env_content = 0;
	var->env_name = 0;
	already_exist_export = 0;
	already_exist_env = 0;
	var->equal_env = 0;
	j = ft_strlen(args) - export_name_len(var, args);
	already_exist_export = name_already_exist(var, args, EXPORT);
	var->export_name = env_name_init(var, args);
	already_exist_env = name_already_exist(var, args, ENV);
	var->env_name = env_name_init(var, args);
	if (j > 0 && var->equal_env == 1)
	{
		var->env_content = env_content_init(var, args, j);
		var->export_content = env_content_init(var, args, j);
	}
	export_assignement(var, i, already_exist_export, already_exist_env);
	return (0);
}

void	export_execution(t_var *var, char *args)
{
	if (export_error_handling(var, args) != -1)
		export_name_content(var, args);
}

int	ft_export(t_var *var)
{
	int		j;

	var->error = 0;
	j = 1;
	if (cmd_export_alone(var) == 1)
	{
		var->exit_status = 0;
		return (EXIT_STATUS);
	}
	while (var->input->args[j])
	{
		if (var->input->args[j][0] == 0)
			unset_error_export_message(var, var->input->args[j]);
		else
			export_execution(var, var->input->args[j]);
		j++;
	}
	EXIT_STATUS = 0;
	if (var->error == 1)
		EXIT_STATUS = 1;
	return (EXIT_STATUS);
}

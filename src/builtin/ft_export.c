/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:45:05 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/22 14:22:17 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_assignement(t_var *var, int i, int equal)
{
	i = export_env_reassigned_check(var, var->export_name,
			var->export_content, equal);
	if (equal == 1 && i != -1)
		export_env_insert(var, var->export_name, var->export_content);
	if (export_export_reassigned_check(var, var->export_name,
			var->export_content, equal) != -1)
		cmd_export_insert(var, var->export_name, var->export_content, equal);
	return (0);
}

int	export_name_init(t_var *var, char *args)
{
	var->export_content = 0;
	var->export_name = 0;
	var->export_name
		= ((char *)malloc(sizeof(char) * (export_name_len(args) + 1)));
	if (!var->export_name)
		return (0);
	return (0);
}

int	export_name_content(t_var *var, char *args)
{
	int		i;
	int		equal;
	int		j;

	i = 0;
	equal = 0;
	j = 0;
	export_name_init(var, args);
	var->export_name
		= export_name_equal_search(args, &i, &equal, var->export_name);
	if (equal == 1)
		j = ft_strlen(args) - export_name_len(args);
	if (j > 0 && equal == 1)
	{
		var->export_content = ((char *) malloc(sizeof(char) * (j + 1)));
		var->export_content
			= export_content_search(&i, args, var->export_content);
		printf("var->export_content = %s\n", var->export_content);
		if (!var->export_name)
			return (0);
	}
	export_assignement(var, i, equal);
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
	printf("COUCOU_1\n");
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

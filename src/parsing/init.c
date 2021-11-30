/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:37:07 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/30 18:46:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_builtin(t_builtin *builtin)
{
	builtin[0].cmd = "echo";
	builtin[0].func = ft_echo;
	builtin[1].cmd = "cd";
	builtin[1].func = ft_cd;
	builtin[2].cmd = "pwd";
	builtin[2].func = ft_pwd;
	builtin[3].cmd = "export";
	builtin[3].func = ft_export;
	builtin[4].cmd = "unset";
	builtin[4].func = ft_unset;
	builtin[5].cmd = "env";
	builtin[5].func = ft_env;
	builtin[6].cmd = "exit";
	builtin[6].func = ft_exit;
	builtin[7].cmd = NULL;
	builtin[7].func = NULL;
}

void	init_var(t_var *var, char **env, int ac)
{
	var->variable = NULL;
	var->exit_code = NULL;
	var->list = NULL;
	var->input = NULL;
	var->s_quote = 0;
	var->d_quote = 0;
	var->cd->cdpath = NULL;
	var->env = env;
	var->ac = ac;
	var->error = 0;
	var->export_name = 0;
	var->export_content = 0;
	var->cd->cdpath_exist = 0;
	var->env_name = 0;
	var->env_content = 0;
	var->equal_env = 0;
	var->reassigned = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:23:03 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/27 18:06:59 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *line, t_builtin *builtin)
{
	int	i;

	i = 0;
	while (builtin[i].cmd)
	{
		if (ft_strcmp(line, builtin[i].cmd) == 1)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	exec_minishell(t_var *var, t_builtin *builtin)
{
	int	ret;

	ret = 0;
	while (1)
	{
		var->cmd = readline("minishell $> ");
		add_history(var->cmd);
		if (get_arguments(var) == FAIL)
		{
			free(var->cmd);
			continue ;
		}
		ret = is_builtin(var->cmd, builtin);
		if (ret >= 0)
			builtin[ret].func(var);
		else if (count_pipes(var) > 1)
			ft_multipipes(var);
		else
			ft_execve(var);
		free_input(var);
		free(var->cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	t_builtin	*builtin;
	t_var		var[1];
	t_envar		*envar;
	t_envar		*export;

	builtin = malloc(sizeof(t_builtin) * 8);
	var->cd = (t_cd *)malloc(sizeof(t_cd));
	init_builtin(builtin);
	init_var(var, env, ac);
	(void)av;
	envar = NULL;
	export = NULL;
	get_env_var(var, &envar);
	get_env_var(var, &export);
	var->envar = envar;
	var->export = export;
	// get_home_unset_cd(var); // surement a supprimer car on ne gere pas le unset HOME
	signal(SIGINT, handle_sigusr1);
	signal(SIGQUIT, handle_sigusr1);
	exec_minishell(var, builtin);
	return (0);
}

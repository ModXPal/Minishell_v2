/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:23:03 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/26 14:12:51 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		if (s2[i + 1] == 0 && (s1[i + 1] == ' ' || s1[i + 1] == 0))
			return (1);
		i++;
	}
	return (0);
}

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

void	free_list(t_var *var)
{
	t_list	*tmp;

	while (var->list)
	{
		tmp = var->list->next;
		free(var->list->content);
		free(var->list);
		var->list = tmp;
	}
}

void	free_split(char **split_str)
{
	int	i;

	i = -1;
	while (split_str[++i])
		free(split_str[i]);
	free(split_str);
}

void	free_envar(t_envar *envar)
{
	t_envar	*tmp;

	while (envar)
	{
		tmp = envar->next;
		free(envar->name);
		free(envar->content);
		free(envar);
		envar = tmp;
	}
}

void	free_input(t_var *var)
{
	int	i;

	i = 0;
	while ((var->input->args)[i])
		free((var->input->args)[i++]);
	free(var->input);
}

int	main(int ac, char **av, char **env)
{
	int			ret;
	int			i;
	int			j;
	t_builtin	*builtin;
	t_var		var[1];
	t_envar		*envar;
	t_envar		*export;

	builtin = malloc(sizeof(t_builtin) * 8);
	var->cd = (t_cd *)malloc(sizeof(t_cd));
	init_builtin(builtin);
	i = -1;
	j = 0;
	ret = 0;
	var->env = env;
	var->ac = ac;
	var->variable = NULL;
	var->list = NULL;
	var->input = NULL;
	var->s_quote = 0;
	var->d_quote = 0;
	(void)av;
	envar = NULL;
	export = NULL;
	get_env_var(var, &envar);
	get_env_var(var, &export);
	var->envar = envar;
	var->export = export;
	get_home_unset_cd(var);
	while (1)
	{
		var->cmd = readline("minishell $> ");
		add_history(var->cmd);
		if (get_arguments(var) == FAIL)
			continue ;
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
	return (0);
}

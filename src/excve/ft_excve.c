/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:38:01 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/08 17:38:08 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	free_excve(t_var *var, t_pvar *pvar, t_builtin *builtin)
{
	ft_putstr_fd("minishell: ", 2);
	perror(pvar->cmd);
	free_split(pvar->path);
	free_envar(var->envar);
	free_envar(var->export);
	free(pvar->cmd);
	free(builtin);
	free(var->cd);
	free_input(var);
	rl_clear_history();
	g_exit_status = 127;
}

void	handle_g_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		g_exit_status = WEXITSTATUS(status);
		if (g_exit_status == 1234567890)
			g_exit_status = 130;
	}
}

int	ft_exec(t_var *var, t_pvar *pvar, int pipe_fd[2], t_builtin *builtin)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_dup(var, pipe_fd) == 1)
		{
			g_exit_status = 1;
			return (g_exit_status);
		}
		close_fd(var);
		if (execve(pvar->cmd, var->input->args, var->env) == -1)
		{
			free_excve(var, pvar, builtin);
			exit (g_exit_status);
		}
	}
	waitpid(0, &status, WUNTRACED);
	handle_g_exit_status(status);
	close_fd(var);
	free_split(pvar->path);
	return (1);
}

int	ft_execve(t_var *var, t_builtin *builtin)
{
	t_pvar	pvar[1];
	int		ret;
	int		pipe_fd[2];

	ret = is_builtin(var->input->cmd, builtin);
	var->pvar = pvar;
	pvar->cmd = NULL;
	if (check_cmd(var) == -1)
		return (-1);
	if (check_ret(ret, var, builtin, pipe_fd) != -216)
		return (g_exit_status);
	pvar->path = get_binaries_path(var);
	add_slash(pvar);
	if (get_cmds(pvar, var) == 0)
	{
		ft_free(pvar->cmd);
		free_split(pvar->path);
		return (-1);
	}
	if (ret < 0)
		ft_exec(var, pvar, pipe_fd, builtin);
	if (pvar->cmd)
		ft_free(pvar->cmd);
	return (g_exit_status);
}

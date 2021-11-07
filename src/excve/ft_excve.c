/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:48:22 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/07 11:50:39 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_execve(t_var *var, t_builtin *builtin)
{
	pid_t	pid;

	int 	status;
	int	ret;
	int	saved_stdout;
	int	saved_stdin;
	int	pipe_fd[2];
	t_pvar	pvar[1];

	ret = is_builtin(var->cmd, builtin);
	if (ret >= 0)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		if (var->input->IN_FD > 0)
			dup2(var->input->IN_FD, STDIN_FILENO);
		if (var->input->OUT_FD > 0)
			dup2(var->input->OUT_FD, STDOUT_FILENO);
		if (var->input->heredoc)
		{
			pipe(pipe_fd);
			write (pipe_fd[1], var->input->heredoc,
				   ft_strlen(var->input->heredoc));
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		builtin[ret].func(var);
		if (var->input->IN_FD > 0)
			close(var->input->IN_FD);
		if (var->input->OUT_FD > 0)
			close(var->input->OUT_FD);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		return (0);
	}
	if (ret == -1)
	{
		EXIT_STATUS = 1234567890;
	}
	pvar->path = get_binaries_path(var);
	add_slash(pvar);
	if (get_cmds(pvar, var) == 0)
		return (-1);
	pid = fork();
	if (pid == 0 && ret < 0)
	{	if (var->input->IN_FD > 0)
			dup2(var->input->IN_FD, STDIN_FILENO);
		if (var->input->OUT_FD > 0)
			dup2(var->input->OUT_FD, STDOUT_FILENO);
		if (var->input->heredoc)
		{
			pipe(pipe_fd);
			write (pipe_fd[1], var->input->heredoc,
				   ft_strlen(var->input->heredoc));
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		if (execve(pvar->cmd, var->input->args, NULL) == -1)
		{
			write(2, var->input->args[0],
				 ft_strlen(var->input->args[0]));
			EXIT_STATUS = 127;
			return (EXIT_STATUS);
		}
	}
	waitpid(0, &status, WUNTRACED);
	if (var->input->IN_FD > 0)
		close(var->input->IN_FD);
	if (var->input->OUT_FD > 0)
		close(var->input->OUT_FD);
	free_split(pvar->path);
	if (WIFEXITED(status))
	{
		EXIT_STATUS = WEXITSTATUS(status);
		if (EXIT_STATUS == 1234567890)
			EXIT_STATUS = 130;
	}
	return (EXIT_STATUS);
}

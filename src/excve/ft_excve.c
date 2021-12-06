#include "builtin.h"

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
			exit (g_exit_status);
		}
	}
	waitpid(0, &status, WUNTRACED);
	handle_g_exit_status(status);
	close_fd(var);
	free_split(pvar->path);
	//free (pvar->cmd);
	return (1);
}

int	handle_builtin(t_var *var, int pipe_fd[2], t_builtin *builtin, int ret)
{
	if (ft_dup(var, pipe_fd) == 1)
		return (1);
	builtin[ret].func(var);
	close_fd(var);
	dup2(var->save_stdout, STDOUT_FILENO);
	dup2(var->save_stdin, STDIN_FILENO);
	return (0);
}

int	ft_execve(t_var *var, t_builtin *builtin)
{
	t_pvar	pvar[1];
	int		ret;
	int		pipe_fd[2];

	ret = is_builtin(var->input->cmd, builtin);
	var->pvar = pvar;
	pvar->cmd = NULL;
	if (var->input->cmd == NULL && (var->input->IN_FD > 0 || var->input->OUT_FD > 0 || var->input->heredoc))
		return (-1);
	if (var->input->IN_FD == -1 || var->input->OUT_FD == -1)
		return (-1);
	if (ret >= 0)
	{
		handle_builtin(var, pipe_fd, builtin, ret);
		return (g_exit_status);
	}
	if (ret == -1)
		g_exit_status = 1234567890;
	pvar->path = get_binaries_path(var);
	add_slash(pvar);
	if (get_cmds(pvar, var) == 0)
	{
		free (pvar->cmd);
		free_split(pvar->path);
		return (-1);
	}
	if (ret < 0)
		ft_exec(var, pvar, pipe_fd, builtin);
	if (pvar->cmd)
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
	return (g_exit_status);
}

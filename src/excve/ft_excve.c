#include "builtin.h"

void	handle_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		EXIT_STATUS = WEXITSTATUS(status);
		if (EXIT_STATUS == 1234567890)
			EXIT_STATUS = 130;
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
			EXIT_STATUS = 1;
			return (EXIT_STATUS);
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
			EXIT_STATUS = 127;
			exit (EXIT_STATUS);
		}
	}
	waitpid(0, &status, WUNTRACED);
	handle_exit_status(status);
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
	if (var->input->cmd == NULL || var->input->cmd[0] == '\0')
		return (-1);
	if (ret >= 0)
	{
		handle_builtin(var, pipe_fd, builtin, ret);
		return (EXIT_STATUS);
	}
	if (ret == -1)
		EXIT_STATUS = 1234567890;
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
	if (pvar->cmd/* && var->cmd[0] != '/' && var->cmd[0] != '.'*/)
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
	return (EXIT_STATUS);
}

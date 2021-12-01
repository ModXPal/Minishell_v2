#include "multipipes.h"

int	check_access(t_pvar *pvar, int i)
{
	if (pvar->cmd == 0)
		return (0);
	if (i == -1)
	{
		if (access(pvar->cmd, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	else if (access(pvar->cmd, X_OK) == -1 && pvar->path[i + 1] == 0)
		return (0);
	else if (access(pvar->cmd, X_OK) == 0)
		return (1);
	return (-1);
}

int	check_relative_exec(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "./", 2) == 0)
		return (1);
	if (ft_strncmp(str, "../", 3) == 0)
		return (2);
	return (0);
}

int	get_prog_path(t_pvar *pvar, t_var *var)
{
	if (check_relative_exec(var->input->cmd) == 1)
	{
		pvar->cmd = ft_strdup(&(var->input->cmd[2]));
		return (0);
	}
	else if (check_relative_exec(var->input->cmd) == 2)
	{
		pvar->cmd = ft_strdup(var->input->cmd);
		return (0);
	}
	return (1);
}

int	executable_error(t_var *var, t_pvar *pvar)
{
	(void)var;
	DIR	*dir;
	if (access(pvar->cmd, X_OK) == -1)
	{
		write (2, "minishell: ", 11);
		perror(pvar->cmd);
		EXIT_STATUS = 127;
		return (0);
	}
	if ((dir = opendir(pvar->cmd)) != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pvar->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		EXIT_STATUS = 127;
		return (0);
	}
	return (1);
}

int	check_input(t_pvar *pvar, t_var *var)
{
	DIR	*dir;

	//if (var->input->args == NULL)
	//	return (0);
	if (get_prog_path(pvar, var) == 0)
	{
		dir = opendir(pvar->cmd);
		if (check_access(pvar, -1) == SUCCESS && dir == NULL)
		{
			return (1);
		}
		else if (check_access(pvar, -1) == FAIL || dir != NULL)
		{
			closedir(dir);
			return (executable_error(var, pvar));
		}
		closedir(dir);
	}
	if (!var->input->cmd || var->input->cmd[0] == '\0')
	{
		pvar->cmd = ft_strdup("");
		return (cmd_not_found(var));
	}
	if (var->input->cmd[0] == '/')
	{
		pvar->cmd = ft_strdup(var->input->cmd);
		if (check_access(pvar, -1) == SUCCESS)
			return (1);
		else if (check_access(pvar, -1) == FAIL)
			return (no_such_file(var));
	}
	return (-1);
}

int	get_cmds(t_pvar *pvar, t_var *var)
{
	int		i;
	int		ret;

	i = -1;
	ret = check_input(pvar, var);
	if (ret == 1)
	{
		//free (pvar->cmd);
		return (1);
	}
	else if (ret == 0)
	{
		//free_split(pvar->path);
		return (0);
	}
	while (pvar->path[++i])
	{
		pvar->cmd = ft_strjoin(pvar->path[i], var->input->cmd);
		if (check_access(pvar, i) == SUCCESS)
			break;
		else if (check_access(pvar, i) == FAIL)
		{
			//free_split(pvar->path);
			//free(pvar->cmd);
			return (cmd_not_found(var));
		}
		free(pvar->cmd);
	}
	return (1);
}

int	exec_execution(t_var *var, pid_t *pids, int **pipefd, t_pvar *pvar)
{
	int	i;

	i = -1;
	var->to_free = var->input;
	while (++i < pvar->cmd_nb)
	{
		dup2(var->save_stdin, STDIN_FILENO);
		dup2(var->save_stdout, STDOUT_FILENO);
		if (i > 0)
			var->input = var->input->next;
		//if (var->input && var->input->cmd)
		pvar->ret = is_builtin(var->input->cmd, pvar->builtin);
		if (pvar->ret == 6)
			return (0);
		if (pvar->ret == -1 && get_cmds(pvar, var) == FAIL)
		{
			free (pvar->cmd);
			pvar->cmd = NULL;
			continue;
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Fork failed:");
			return (1);
		}
		if (pids[i] == 0)
		{
			if (pvar->ret >= 0)
				proceed_builtin_pipes(pvar, var, pipefd, i);
			else
				proceed_pipes(pvar, var, pipefd, i);
			break ;
		}
		if (pvar->cmd)
		{
			free(pvar->cmd);
			pvar->cmd = NULL;
		}
	}
	return (0);
}

int	exec(t_pvar *pvar, t_var *var, int **pipefd, pid_t *pids)
{
	int		i;
	int		status;
	t_input	*start;

	start = var->input;
	status = 0;
	if (exec_execution(var, pids, pipefd, pvar) == 1)
		return (1);
	close_pipes(pvar, pipefd);
	close_fd(var);
	i = -1;
	while (++i < pvar->cmd_nb)
		waitpid(0, &status, 0);
	multipipes_signal_handling(status);
	free(pids);
	var->input = start;
	free_split(pvar->path);
	if (pvar->cmd)
	{
		free(pvar->cmd);
		pvar->cmd = NULL;
	}
	pipefd = NULL;
	return (EXIT_STATUS);
}

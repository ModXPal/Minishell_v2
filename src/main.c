#include "minishell.h"

int	g_exit_status;

int	is_builtin(char *line, t_builtin *builtin)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (-1);
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

int	restore_fd(t_var *var)
{
	if (var->input->IN_FD > 0)
	{
		close(var->input->IN_FD);
		dup2(var->save_stdin, STDIN_FILENO);
	}
	if (var->input->OUT_FD > 0)
	{
		close(var->input->OUT_FD);
		dup2(var->save_stdout, STDOUT_FILENO);
	}
	if (var->input)
		free_input(var);
	if (var->cmd)
		free(var->cmd);
	return (0);
}

int	boucle_exec_minishell(t_var *var, t_builtin *builtin)
{
	if (get_arguments(var) == -1)
	{
		free(var->cmd);
		return (0);
	}
	else if (var->input == NULL)
	{
		free_input(var);
		free(var->cmd);
		return (0);
	}
	else if (var->cmd_nb > 1)
	{
		g_exit_status = 123456789;
		ft_multipipes(var, builtin);
	}
	else
		ft_execve(var, builtin);
	dup2(var->save_stdin, STDIN_FILENO);
	dup2(var->save_stdout, STDOUT_FILENO);
	if (var->input->heredoc)
		free(var->input->heredoc);
	restore_fd(var);
	return (0);
}

int	exec_minishell(t_var *var, t_builtin *builtin)
{
	var->save_stdin = dup(STDIN_FILENO);
	var->save_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		ft_putstr_fd("on est de retour\n", 2);
		var->cmd = readline("minishell $> ");
		if (!var->cmd)
		{
			free(var->cd);
			free_list(var);
			//free_input(var);
			free (builtin);
			free_envar(var->envar);
			free_envar(var->export);
			rl_clear_history();
			break ;
		}
		add_history(var->cmd);
		boucle_exec_minishell(var, builtin);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_builtin	*builtin;
	t_var		var[1];
	t_envar		*envar;
	t_envar		*export;

	if (*env == NULL)
	{
		ft_putstr_fd("Basic environment variables are missing\n", 2);
		exit (1);
	}
	builtin = malloc(sizeof(t_builtin) * 8);
	var->cd = (t_cd *)malloc(sizeof(t_cd));
	init_builtin(builtin);
	var->builtin = builtin;
	init_var(var, env, ac);
	(void)av;
	envar = NULL;
	var->cd->exit_cd = 0;
	var->trim_expand = NULL;
	export = NULL;
	g_exit_status = 0;
	get_env_var(var, &envar);
	get_env_var(var, &export);
	var->envar = envar;
	var->export = export;
	signal(SIGINT, handle_sigusr1);
	signal(SIGQUIT, handle_sigusr1);
	signal(SIGTSTP, handle_sigusr1);
	exec_minishell(var, builtin);
	return (0);
}

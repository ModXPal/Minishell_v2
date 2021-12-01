#include "builtin.h"

int	exit_with_digits(t_var *var)
{
	int		i;

	i = 0;
	i = ft_atoi(var->input->args[1]);
	ft_putendl_fd("exit", 2);
	close(var->save_stdin);
	close(var->save_stdout);
	free(var->cd);
	free(var->builtin);
	free_input(var);
	free_envar(var->envar);
	free_envar(var->export);
	rl_clear_history();
	EXIT_STATUS = i;
	exit (EXIT_STATUS);
}

int	exit_with_too_many_arguments(t_var *var)
{
	if (split_len(var->input->args) > 2)
	{
		ft_putendl_fd("exit", 2);
		write(2, "minishell: ", 12);
		write(2, var->input->cmd, ft_strlen(var->input->cmd));
		ft_putendl_fd(": too many arguments", 2);
		close(var->save_stdin);
		close(var->save_stdout);
		free(var->builtin);
		free(var->cd);
		free_input(var);
		free_envar(var->envar);
		free_envar(var->export);
		rl_clear_history();
		EXIT_STATUS = 1;
		exit (EXIT_STATUS);
	}
	return (0);
}

int	exit_with_errors(t_var *var)
{
	int		i;

	i = 0;
	while (var->input->args[1][i])
	{
		if (!ft_isdigit(var->input->args[1][i]))
		{
			ft_putendl_fd("exit", 2);
			write (2, "minishell: ", 12);
			write(2, var->input->cmd, ft_strlen(var->input->cmd));
			write (2, ": ", 2);
			write(2, var->input->args[1], ft_strlen(var->input->args[1]));
			ft_putendl_fd(": numeric argument required", 2);
			close(var->save_stdin);
			close(var->save_stdout);
			free(var->cd);
			free(var->builtin);
			free_input(var);
			free_envar(var->envar);
			free_envar(var->export);
			rl_clear_history();
			EXIT_STATUS = 1;
			exit (EXIT_STATUS);
		}
		i++;
	}
	return (0);
}

int	exit_without_cmd(t_var *var)
{
	if (var->input->args[1] == 0)
	{
		ft_putendl_fd("exit", 2);
		close(var->save_stdin);
		close(var->save_stdout);
		free(var->cd);
		free(var->builtin);
		free_input(var);
		free_envar(var->envar);
		free_envar(var->export);
		rl_clear_history();
		EXIT_STATUS = 0;
		exit (EXIT_STATUS);
	}
	return (0);
}

int	ft_exit(t_var *var)
{
	int	i;

	i = 0;
	exit_without_cmd(var);
	exit_with_too_many_arguments(var);
	exit_with_errors(var);
	exit_with_digits(var);
	close(var->save_stdin);
	close(var->save_stdout);
	free(var->cd);
	free(var->builtin);
	free_input(var);
	free_envar(var->envar);
	free_envar(var->export);
	rl_clear_history();
	return (0);
}

#include "parsing.h"

void	open_files(t_input *input, char *file, int redir)
{
	if (redir == STDIN)
	{
		input->IN_FD = open(file, O_RDONLY);
		if (input->IN_FD < 0)
			missing_file(file);
	}
	else if (redir == STDOUT)
	{
		input->OUT_FD = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (input->OUT_FD < 0)
			permission_denied(file);
	}
	else if (redir == STDOUT_APPEND)
	{
		input->OUT_FD = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (input->OUT_FD < 0)
			permission_denied(file);
	}
}

int	handle_in_redir(t_var *var, t_input *input, char **split_input, int *i)
{
	int	len;

	len = get_string_len(split_input[(*i) + 1], var);
	if (ft_strcmp(split_input[*i], "<") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), STDIN);
		if (input->IN_FD > 0)
			return (0);
		else
			return (2);
	}
	else if (ft_strcmp(split_input[*i], "<<") == TRUE)
	{
		(*i)++;
		here_doc(input, ft_trim(var, split_input[*i], len), var);
		return (1);
	}
	return (-1);
}

int	handle_out_redir(t_var *var, t_input *input, char **split_input, int *i)
{
	int	len;

	len = get_string_len(split_input[(*i) + 1], var);
	if (ft_strcmp(split_input[*i], ">") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), STDOUT);
		if (input->OUT_FD > 0)
			return (0);
		else
			return (2);
	}
	else if (ft_strcmp(split_input[*i], ">>") == TRUE)
	{
		(*i)++;
		open_files(input, ft_trim(var, split_input[*i], len), STDOUT_APPEND);
		if (input->OUT_FD > 0)
			return (0);
		else
			return (2);
	}
	return (-1);
}

int	handle_redir(t_var *var, t_input *input, char **split_input, int *i)
{
	int	ret;

	ret = handle_in_redir(var, input, split_input, i);
	if (ret == 0)
		return (0);
	else if (ret == 1)
		return (1);
	else if (ret == 2)
		return (2);
	ret = handle_out_redir(var, input, split_input, i);
	if (ret == 0)
		return (0);
	else if (ret == 2)
		return (2);
	return (-1);
}

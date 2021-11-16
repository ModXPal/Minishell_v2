/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/04 13:47:40 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_valid_envar(t_var *var, char *str, int i)
{
	t_envar	*tmp;
	int		j;
	int		k;

	tmp = var->envar;
	while (tmp)
	{
		j = 0;
		k = i;
		while (tmp->name[j] && str[k])
		{
			if (ft_charcmp((tmp->name)[j], str[k]) == FAIL)
				break ;
			j++;
			k++;
			if ((ft_isalnum(str[k]) == 0) || str[k] == 0)
				return (tmp->content);
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*ft_trim(t_var *var, char *str, int len)
{
	char	*trim_str;
	int		i;
	int		j;
	int		k;

	trim_str = (char *)malloc(sizeof(char) * (len + 1));
	j = 0;
	i = 0;
	while (i < len)
	{
		k = 0;
		if (check_quotes(str, &j, var) == TRUE)
			continue ;
		if (str[j] == '$' && var->s_quote == FALSE && ft_isalnum(str[j + 1]))
		{
			j++;
			while (get_valid_envar(var, str, j)[k])
				trim_str[i++] = get_valid_envar(var, str, j)[k++];
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	trim_str[i] = 0;
	return (trim_str);
}

char	*trim_heredoc(char *str, int len, t_var *var)
{
	char	*trim_str;
	int		i;
	int		j;
	int		k;

	trim_str = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (i < len)
	{
		k = 0;
		if (str[j] == '$' && ft_isalnum(str[j + 1]))
		{
			j++;
			while (get_valid_envar(var, str, j)[k])
				trim_str[i++] = get_valid_envar(var, str, j)[k++];
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	trim_str[i] = 0;
	free (str);
	return (trim_str);
}

int	count_pipes(t_var *var)
{
	int	i;
	int	pipe_count;
	int s_quote;
	int d_quote;

	i = -1;
	pipe_count = 1;
	s_quote = 0;
	d_quote = 0;
	while (var->cmd[++i])
	{
		if (var->cmd[i] == '"' && s_quote == FALSE)
			check_d_quote(&d_quote);
		if (var->cmd[i] == '\'' && d_quote == FALSE)
			check_s_quote(&s_quote);
		if (var->cmd[i] == '|' && s_quote == FALSE && d_quote == FALSE)
			pipe_count++;
	}
	return (pipe_count);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	syntax_error(char **input, int i, int j)
{
	if (j == 2)
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][0], 2);
		write (2, "'\n", 2);
	}
	else if (j == 3)
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][0], ft_strlen(&input[i][0]));
		write (2, "'\n", 2);
	}
	else if (input[i][0] == '<' && input[i][1] == '>')
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][1], ft_strlen(&input[i][1]));
		write (2, "'\n", 2);
	}
	else if (input[i][0] == '>' && input[i][1] == '<')
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, &input[i][1], ft_strlen(&input[i][1]));
		write (2, "'\n", 2);
	}
	else
	{
		write (2, "minishell: syntax error near unexpected token `", 47);
		write (2, "newline", 7);
		write (2, "'\n", 2);
	}
	return (-1);
}

int	syntax_check(char **input)
{
	int	i;
	int	j;

	i = -1;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j] == '<')
		{
			if (j == 2)
				return (syntax_error(input, i, j));
			else if (input[i][j + 1] == '>')
				return (syntax_error(input, i, j));
			else if (input[i + 1] == NULL && input[i][j + 1] != '<')
				return (syntax_error(input, i, j));
			else if (input[i + 1] && (input[i + 1][0] == '>' || input[i + 1][0] == '<'))
				return (syntax_error(input, i + 1, 3));
		}
		j = -1;
		while (input[i][++j] == '>')
		{
			if (j == 2)
				return (syntax_error(input, i, j));
			else if (input[i][j + 1] == '<')
				return (syntax_error(input, i, j));
			else if (input[i + 1] == NULL && input[i][j + 1] != '>')
				return (syntax_error(input, i, j));
			else if (input[i + 1] && (input[i + 1][0] == '<' || input[i + 1][0] == '>'))
				return (syntax_error(input, i + 1, 3));
		}
	}
	return (0);
}

char	*delete_last_line(char *str)
{
	int	i;
	char	*final_str;
	char	*tmp;

	if (str == NULL)
		return (NULL);
	tmp = str;
	i = ft_strlen(str) - 2;
	while (str[i - 1] != '\n')
		i--;
	final_str = malloc(sizeof(char) * i);
	if (final_str == 0)
		return (NULL);
	final_str[i] = 0;
	while (--i >= 0)
		final_str[i] = str[i];
	free (str);
	return (final_str);
}

int	here_doc(t_input *input, char *delimiter, t_var *var)
{
	char    *line;
	char	*tmp;
	char	buff[2];
	int		ret;
	int		i;
	int		j;

	line = ft_strdup("");
	j = 0;
	i = 0;
	input->IN_FD = 0;
	while (ft_strcmp(&line[ft_strlen(line) - i], delimiter) == 0)
	{
		if (i != 0)
			line = ft_strjoin(line, "\n");
		i = 0;
		ret = 1;
		buff[0] = 0;
		write(STDOUT_FILENO, "> ", 2);
		while (ret > 0 && buff[0] != '\n')
		{
			ret = read(STDIN_FILENO, buff, 1);
			buff[1] = 0;
			if (buff[0] != '\n')
				line = ft_strjoin(line, buff);
			i++;
		}
		i--;
	}
	tmp = line;
	line = ft_strjoin(line, "\n");
	free(tmp);
	line = delete_last_line(line);
	if (input->heredoc)
		free(input->heredoc);
	input->heredoc = trim_heredoc(line, get_heredoc_len(line, var), var);
	return (0);
}

void	missing_file(char *file)
{
	write (2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	write (2, ": No such file or directory\n", 28);
}

void 	permission_denied(char *file)
{
	write (2, "minishell: ", 11);
	write (2, file, ft_strlen(file));
	write (2, ": Permission denied\n", 20);
}

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

int	handle_redir(t_var *var, t_input *input, char **split_input, int *i)
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
	else if (ft_strcmp(split_input[*i], ">") == TRUE)
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

int	handle_input(t_var *var, t_input *new, char **split_input)
{
	int	i;
	int	j;
	int	len;
	int	ret;
	char	*content;

	i = -1;
	j = 0;
	ret = 0;
	while (split_input[++i])
	{
		var->s_quote = 0;
		var->d_quote = 0;
		len = get_string_len(split_input[i], var);
		var->s_quote = 0;
		var->d_quote = 0;
		content = ft_trim(var, split_input[i], len);
		ret = handle_redir(var, new, split_input, &i);
		if (ret == 0 || ret == 1)
			continue;
		else if (ret == 2)
			return (1);
		else if (i == 0 || ((new->IN_FD > 0 || new->OUT_FD > 0 || new->heredoc) && new->cmd == NULL))
			new->cmd = content;
		new->args[j++] = content;
	}
	new->args[j] = NULL;
	new->next = NULL;
	if (new->cmd == NULL)
		return (1);
	return (0);
}

int	count_heredoc(char **split_input)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (split_input[++i])
	{
		if (ft_strcmp(split_input[i], "<<") == TRUE)
			count++;
	}
	return (count);
}

t_input	*get_input(t_var *var, char **split_input)
{
	int		i;
	int		j;
	t_input	*new;

	i = -1;
	new = malloc(sizeof(t_input));
	if (new == 0)
		return (0);
	new->args = (char **)malloc(sizeof(char *) * (split_len(split_input) + count_heredoc(split_input) + 1));
	if (new->args == FAIL)
		return (0);
	new->cmd = NULL;
	new->IN_FD = 0;
	new->OUT_FD = 0;
	new->heredoc = 0;
	i = -1;
	j = 0;
	if (handle_input(var, new, split_input) == 1)
		return (0);
		//printf("in fd = %d\n", var->IN_FD);
	//printf("out fd = %d\n", var->OUT_FD);
	return (new);
}

t_input	*ft_inptlast(t_input *input)
{
	if (!input)
		return (NULL);
	while (input)
	{
		if (input->next == NULL)
			return (input);
		input = input->next;
	}
	return (NULL);
}

void	input_add_back(t_input **ainpt, t_input *new)
{
	t_input	*last;

	if (!ainpt || !new)
		return ;
	if (*ainpt)
	{
		last = ft_inptlast(*ainpt);
		last->next = new;
	}
	else
		*ainpt = new;
}

int pipe_error(void)
{
	write (2, "minishell: syntax error near unexpected token `", 47);
	write (2, "|", 1);
	write (2, "'\n", 2);
	return (-1);
}

int check_pipes(t_var *var)
{
	int i;
	_Bool non_empty;

	i = -1;
	non_empty = FALSE;
	while (var->cmd[++i])
	{
		if (var->cmd[i] != ' ' && var->cmd[i] != '|')
			non_empty = TRUE;
		else if (non_empty == FALSE && var->cmd[i] == '|')
			return (pipe_error());
		else if (var->cmd[i] == '|')
			non_empty = FALSE;
	}
	if (non_empty == FALSE)
		return (pipe_error());
	return (0);
}

int	get_arguments(t_var *var)
{
	char	**split_input;
	char	**split_pipes;
	int		i;
	t_input	*new;

	i = -1;
	var->cmd_nb = count_pipes(var);
	if (var->cmd[0] == 0)
		return (-1);
	if (check_unmatched_quotes(var) == TRUE)
	{
		printf("Unmatched quotes\n");
		return (-1);
	}
	if (check_pipes(var) == -1)
		return (-1);
	split_pipes = ft_split_pipes(var->cmd, '|');
	var->input = NULL;
	while (split_pipes[++i])
	{
		split_input = ft_split_quotes(split_pipes[i], ' ');
		if (syntax_check(split_input) == -1)
			return (-1);
		new = get_input(var, split_input);
		if (new != NULL)
		{
			input_add_back(&var->input, new);
		}
		else
			var->cmd_nb--;
		free_split(split_input);
	}
	free_split(split_pipes);
	return (0);
}
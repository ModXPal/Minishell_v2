/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/12/03 15:08:09 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_trim_delimiter(t_var *var, char *str, int len)
{
	char	*trim_str;
	int		i;
	int		j;

	trim_str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!trim_str)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (check_quotes(str, &j, var) == TRUE)
		{
			var->expand = 0;
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	return (trim_str);
}

t_input	*get_input(t_var *var, char **split_input)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (new == 0)
		return (0);
	new->args = (char **)ft_calloc(sizeof(char *),
			(split_len(split_input) + 1));
	new->cmd = NULL;
	new->in_fd = 0;
	new->out_fd = 0;
	new->heredoc = 0;
	handle_input(var, new, split_input);
	if (new->cmd == NULL)
	{
		if (split_len(split_input) + 1 == 1)
		{
			free(new->args);
			new->args = NULL;
		}
		return (new);
	}
	return (new);
}

int	create_input_list(t_var *var, char *split_pipes)
{
	t_input	*new;
	char	**split_input;

	split_input = ft_split_quotes(split_pipes, ' ');
	if (syntax_check(split_input) == -1)
	{
		free_split (split_input);
		return (-1);
	}
	new = get_input(var, split_input);
	input_add_back(&var->input, new);
	free_split(split_input);
	return (0);
}

int	check_syntax(t_var *var)
{
	if (var->cmd[0] == 0)
		return (-1);
	if (check_unmatched_quotes(var) == TRUE)
	{
		printf("Unmatched quotes\n");
		g_exit_status = 1;
		return (-1);
	}
	if (check_pipes(var) == -1)
	{
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	get_arguments(t_var *var)
{
	char	**split_pipes;
	int		i;

	i = -1;
	if (check_syntax(var) == -1)
		return (-1);
	var->cmd_nb = count_pipes(var);
	split_pipes = ft_split_pipes(var->cmd, '|');
	var->input = NULL;
	while (split_pipes[++i])
	{
		if (create_input_list(var, split_pipes[i]) == -1)
		{
			free_split(split_pipes);
			return (-1);
		}
	}
	free_split(split_pipes);
	return (0);
}

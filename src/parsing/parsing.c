/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:41:26 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/27 17:48:52 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_input	*get_input(t_var *var, char **split_input)
{
	int		i;
	int		len;
	char	*content;
	t_input	*new;

	i = -1;
	new = malloc(sizeof(t_input));
	new->args = (char **)malloc(sizeof(char *) * (split_len(split_input) + 1));
	if (new->args == FAIL)
		return (0);
	while (split_input[++i])
	{
		var->s_quote = 0;
		var->d_quote = 0;
		len = get_string_len(split_input[i], var);
		var->s_quote = 0;
		var->d_quote = 0;
		content = ft_trim(var, split_input[i], len);
		if (i == 0)
			new->cmd = content;
		new->args[i] = content;
	}
	new->args[i] = NULL;
	new->next = NULL;
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

int	get_arguments(t_var *var)
{
	char	**split_input;
	char	**split_pipes;
	int		i;
	t_input	*new;

	i = -1;
	if (var->cmd[0] == 0)
		return (0);
	if (check_unmatched_quotes(var) == TRUE)
	{
		printf("Unmatched quotes\n");
		return (0);
	}
	split_pipes = ft_split(var->cmd, '|');
	var->input = NULL;
	while (split_pipes[++i])
	{
		split_input = ft_split_quotes(split_pipes[i], ' ');
		new = get_input(var, split_input);
		input_add_back(&var->input, new);
		free_split(split_input);
	}
	free_split(split_pipes);
	return (1);
}

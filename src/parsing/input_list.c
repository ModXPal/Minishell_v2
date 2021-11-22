#include "parsing.h"

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

void	init_input(t_var *var, char *split, char **content)
{
	int	len;

	var->s_quote = 0;
	var->d_quote = 0;
	len = get_string_len(split, var);
	var->s_quote = 0;
	var->d_quote = 0;
	*content = ft_trim(var, split, len);
}

int	handle_input(t_var *var, t_input *new, char **split_input)
{
	int		i;
	int		j;
	int		ret;
	char	*content;

	i = -1;
	j = 0;
	while (split_input[++i])
	{
		init_input(var, split_input[i], &content);
		ret = handle_redir(var, new, split_input, &i);
		if (ret == 0 || ret == 1)
			continue ;
		else if (ret == 2)
			return (2);
		else if (i == 0 || ((new->IN_FD > 0 || new->OUT_FD > 0
					 || new->heredoc) && new->cmd == NULL))
			new->cmd = content;
		new->args[j++] = content;
	}
	new->args[j] = NULL;
	new->next = NULL;
	return (0);
}

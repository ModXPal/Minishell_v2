#include "parsing.h"

char	*delete_last_line(char *str)
{
	int		i;
	char	*final_str;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 2;
	while (i >= 1 && str[i - 1] != '\n')
		i--;
	final_str = malloc(sizeof(char) * (i + 1));
	if (final_str == 0)
		return (NULL);
	final_str[i] = 0;
	while (--i >= 0)
		final_str[i] = str[i];
	free (str);
	return (final_str);
}

char	*trim_heredoc(char *str, int len, t_var *var)
{
	char	*trim_str;
	char	*tmp;
	int		i;
	int		j;

	trim_str = ft_calloc(sizeof(char), (len + 1));
	if (!trim_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[j] == '$' && ft_isalnum(str[j + 1]) && var->expand)
		{
			j++;
			tmp = get_valid_envar(var, str, j);
			assign_envar(tmp, trim_str, &i);
			skip_alnum(str, &j);
			continue ;
		}
		trim_str[i++] = str[j++];
	}
	free (str);
	var->expand = 1;
	return (trim_str);
}

void	get_line(char *buff, char *tmp, char **line)
{
	buff[1] = 0;
	if (buff[0] != '\n')
	{
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free (tmp);
	}
}

void	get_next_line(char **line, int *i)
{
	char	buff[2];
	int		ret;
	char	*tmp;

	if (*i != 0)
	{
		tmp = *line;
		*line = ft_strjoin(*line, "\n");
		free (tmp);
	}
	*i = 0;
	ret = 1;
	buff[0] = 0;
	g_exit_status = 300;
	write(STDOUT_FILENO, "> ", 2);
	while (ret > 0 && buff[0] != '\n')
	{
		ret = read(STDIN_FILENO, buff, 1);
		get_line(buff, tmp, line);
		(*i)++;
	}
	(*i)--;
}

int	here_doc(t_input *input, char *delimiter, t_var *var)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	line = ft_strdup("");
	input->IN_FD = 0;
	while (ft_strcmp(&line[ft_strlen(line) - i], delimiter) == 0)
		get_next_line(&line, &i);
	tmp = line;
	line = ft_strjoin(line, "\n");
	free(tmp);
	line = delete_last_line(line);
	if (input->heredoc)
		free(input->heredoc);
	input->heredoc = trim_heredoc(line, get_heredoc_len(line, var), var);
	free (delimiter);
	return (0);
}

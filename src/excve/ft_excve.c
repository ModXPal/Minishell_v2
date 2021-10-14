/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:48:22 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/14 17:49:49 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_path(t_var *var, char**path_fromenvp)
{
	char	*path_final;
	char	*path_semi_final;
	int		i;

	i = 0;
	while (path_fromenvp[i])
	{
		path_final = 0;
		path_semi_final = ft_strjoin(path_fromenvp[i], "/");
		path_final = ft_strjoin(path_semi_final, var->list->content);
		if (access(path_final, F_OK) == 0)
			return (path_final);
		if (path_final)
			free (path_final);
		i++;
	}
	if (var->list->content[0] == '/'
		&& access(&var->list->content[0], F_OK) == 0)
		return (&var->list->content[0]);
	return (NULL);
}

int	execve_error(t_var *var)
{
	t_list	*tmp;
	
	tmp = var->list;
	write (2, "minishell: ", 12);
	write(2, tmp->content, ft_strlen(tmp->content));
	ft_putendl_fd(": command not found", 2);
	return (0);
	// FREE DES FONCTIONS ICI
}

// int	excve_is_invalid(t_var *var)
// {
// 	write(2, "minishell: ", 12);
// 	write(2, tmp->content, ft_strlen(tmp->content));
// 	ft_putendl_fd("command not found", 2);
// 	return (-1);
// }

int	ft_execve(t_var *var)
{
	char 	*path_final;
	char	**path_fromenvp;
	t_envar	*tmp;
	t_list	*tmp2;
	char 	*str;
	char 	**str3;

	tmp = var->envar;
	tmp2 = var->list;
	str = NULL;
	path_final = ft_envar_find_content(tmp, "PATH");
	str3 = ft_split(var->cmd, 32);
	path_fromenvp = ft_split(path_final, ':');
	path_final = get_path(var, path_fromenvp);
	if (execve(path_final, str3, NULL) == -1)
		execve_error(var);
	return (0);
}


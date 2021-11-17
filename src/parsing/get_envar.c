/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:25:10 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/29 16:16:58 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_var_name(char **env, int i)
{
	int		j;
	char	*name;

	j = 0;
	while (env[i][j] != '=')
		j++;
	name = (char *)malloc(sizeof(char) * (j + 1));
	name[j] = '\0';
	while (--j >= 0)
		name[j] = env[i][j];
	return (name);
}

char	*get_var_content(char **env, int i)
{
	int		var_len;
	int		j;
	int		k;
	char	*content;

	j = 0;
	k = 0;
	var_len = ft_strlen(env[i]);
	while (env[i][j - 1] != '=')
		j++;
	content = (char *)malloc(sizeof(char) * (var_len - j + 1));
	while (env[i][j])
		content[k++] = env[i][j++];
	content[k] = '\0';
	return (content);
}

void	get_env_var(t_var *var, t_envar **envar)
{
	int		i;
	t_envar	*tmp;

	i = -1;
	while (var->env[++i])
	{
		tmp = ft_envar_new(get_var_name(var->env, i),
				get_var_content(var->env, i));
		ft_envaradd_back(envar, tmp);
	}
}

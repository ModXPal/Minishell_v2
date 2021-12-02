/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:01:39 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/02 12:05:28 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	error_chdir(t_var *var, int dir, char *str)
{
	if (dir < 0)
	{
		errors_chdir_handling(dir, var);
		if (str && var->pwd_exist == 1)
			free (str);
		return (1);
	}
	return (0);
}

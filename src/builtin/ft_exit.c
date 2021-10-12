/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:38 by vbachele          #+#    #+#             */
/*   Updated: 2021/10/12 16:11:39 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_exit(t_var *var)
{
	free_envar(var->envar);
	// rl_clear_history();
	exit (EXIT_SUCCESS);
	return (0);
}

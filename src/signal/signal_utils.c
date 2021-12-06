/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:41:52 by vbachele          #+#    #+#             */
/*   Updated: 2021/12/06 15:56:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	init_signal(t_var *var)
{
	(void) var;
	signal(SIGINT, handle_sigusr1);
	signal(SIGQUIT, handle_sigusr1);
	signal(SIGTSTP, handle_sigusr1);
}

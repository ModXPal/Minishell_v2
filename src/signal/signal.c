/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:34:28 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/06 19:05:15 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	signal_sigint_stdin(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	EXIT_STATUS = 130;
}

void	signal_singint_normal(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	EXIT_STATUS = 130;
}

void	handle_sigusr1(int signum)
{
	if (signum == SIGINT && EXIT_STATUS != 123456789)
		signal_singint_normal();
	else if (signum == SIGINT && EXIT_STATUS == 123456789)
		signal_sigint_stdin();
	else if (signum == SIGQUIT && EXIT_STATUS == 123456789)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "Quit\n", 5);
		EXIT_STATUS = 131;
	}
	else if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

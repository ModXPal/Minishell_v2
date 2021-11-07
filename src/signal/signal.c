/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:34:28 by vbachele          #+#    #+#             */
/*   Updated: 2021/11/07 15:55:09 by vbachele         ###   ########.fr       */
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

void	signal_singint_stdin_multipipe(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	EXIT_STATUS = 0;
}

void	multipipes_signal_handling(int status)
{
	if (WIFEXITED(status) == 0)
	{
		EXIT_STATUS = WIFEXITED(status);
		if (status == 13)
			EXIT_STATUS = 127;
		if (status == 131)
			EXIT_STATUS = 131;
	}
	if (WIFEXITED(status))
	{
		EXIT_STATUS = WEXITSTATUS(status);
		if (EXIT_STATUS == 12346789)
			EXIT_STATUS = 0;
	}
}

void	handle_sigusr1(int signum)
{
	if (signum == SIGINT && EXIT_STATUS != 1234567890 && EXIT_STATUS != 123456789)
		signal_singint_normal();
	else if (signum == SIGINT && isatty(0) != 0 && EXIT_STATUS != 123456789)
		signal_sigint_stdin();
	else if (signum == SIGINT && isatty(0) != 0)
		signal_singint_stdin_multipipe();
	else if ((signum == SIGQUIT && EXIT_STATUS == 123456789) 
		|| (signum == SIGQUIT && EXIT_STATUS== 1234567890))
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "Quit\n", 5);
		EXIT_STATUS = 131;
	}
		else if (signum == SIGQUIT || signum == SIGTSTP)
		write(1, "\b\b  \b\b", 6);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:34:15 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/16 11:34:37 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ctrl c - SIGINT
ctrl d - 
ctrl / - SIGQUIT. we need ti ignore SIG_IGN*/
#include "minishell.h"

#include <signal.h>
#include <stdio.h>



extern long long	g_exit_status;

void	child_signals(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 130;
		exit(130);
	}
}

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/*	CTRL+C
		sigaction(SIGINT, &sa, NULL);
	Ignore CTRL+backslSTDERR_FILENOash
		signal(SIGQUIT, SIG_IGN);
*/

void	sigint_handler(int sig)
{
	//make a new prompt;
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
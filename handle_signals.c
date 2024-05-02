/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:59:10 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/02 11:59:11 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signals_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
rl_replace_line clears the input buffer,
discarding any previous input and clearing the undo list.
rl_on_new_line notifies Readline that the cursor is on a new line, 
typically used to ensure proper display of the prompt for new input.
rl_redisplay requests the GNU Readline library to redisplay the current input line.
This is necessary after modifying the line (such as clearing it)
to ensure that the changes are reflected on the terminal.
*/
void	sigint_handler(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

/*
Function: void rl_replace_line (const char *text, int clear_undo)
Replace the contents of rl_line_buffer with text.
The point and mark are preserved, if possible.
If clear_undo is non-zero, the undo list associated with the current line is cleared.


Function: int rl_on_new_line (void)

Tell the update functions that we have moved onto a new (empty) line,
usually after outputting a newline. 
*/

void	init_signals(void)
{
	t_sigaction	act;
	t_sigaction	ign;

	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	act.sa_handler = &sigint_handler;
	ign.sa_flags = SA_RESTART;
	sigemptyset(&ign.sa_mask);
	ign.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &act, NULL) != 0)
		exit(EXIT_FAILURE);
	if (sigaction(SIGQUIT, &ign, NULL) != 0)
		exit(EXIT_FAILURE);
	// signal(SIGINT, sigint_handler); // ctrl c
	// signal(SIGQUIT, SIG_IGN); //ctrl \ does nothing
}
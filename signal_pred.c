#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
# include <sysexits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include <sys/ioctl.h>
#include <asm/termbits.h> 

typedef struct sigaction t_sigaction;

/*
Function: int rl_on_new_line ()
Tell the update routines that we have moved
onto a new (empty) line,
usually after ouputting a newline

Function: void rl_replace_line (const char *text, int clear_undo)
Replace the contents of rl_line_buffer with text. 
The # include <sysexits.h>point and mark are preserved, if possible. 
If clear_undo is non-zero, the undo list
associated with the current line is cleared.

Function: int rl_redisplay ()
Change what's displayed on the screen 
to reflect the current contents of rl_line_buffer

*/


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

// static void waiting_signal_handler(int signal)
// {
//     if (signal == SIGINT)
//         printf("\n");
//     else if (signal == SIGQUIT)
//         printf("Quit (core dumped)\n");
// }

void	sigint_handler(int sig)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

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
	// rl_event_hook = event;
	// signal(SIGINT, sigint_handler); // ctrl c
	// signal(SIGQUIT, SIG_IGN); //ctrl \ does nothing
}

int	main(void)
{
	char *input;

	init_signals();
	while(true)
	{
		input = readline("minishell>");
		if (input == NULL)
			break;
		add_history(input);
	}
	free(input);
	rl_clear_history();
	return (0);
}

//SIGINT and SIGQUIT to defult in child process

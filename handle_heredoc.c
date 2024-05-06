/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:33:59 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/02 17:34:10 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_err(t_data *vars, t_list *list)
{
	unlink(".heredoc_tmp");
	perror("file descriptor error\n");
	// FREE all malloced in structure before execution!!!!!!! 
	//нужно то что в листе замалочено убрать. временно сделаем это>>
	free(list);
	free_pipes(vars);
	exit(1);
}

void	sigint_handler_hd(int sig)
{
	ft_putstr_fd("^C\n", STDOUT_FILENO);
//	rl_replace_line("", 1);
//	rl_on_new_line();
//	rl_redisplay();
	(void) sig;
}

void	signals_hd(void)
{
	// t_sigaction	act;
	// t_sigaction	ign;

	// act.sa_flags = SA_RESTART;
	// sigemptyset(&act.sa_mask);
	// act.sa_handler = &sigint_handler_hd;
	// ign.sa_flags = SA_RESTART;
	// sigemptyset(&ign.sa_mask);
	// ign.sa_handler = SIG_IGN;
	// if (sigaction(SIGINT, &act, NULL) != 0)
	// 	exit(EXIT_FAILURE);
	// if (sigaction(SIGQUIT, &ign, NULL) != 0)
	// 	exit(EXIT_FAILURE);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	hd(t_list *list, int *fd)
{
	char	*line;
	char	*copy_line;
	int		i;

	line = readline("> ");
	if (line == NULL)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 1);
		ft_putstr_fd(list->inf->file, 1);
		ft_putstr_fd("')\n", STDOUT_FILENO);
		exit (0);
		//return (0);
	}
	if (!line)
		exit(1);
	i = ft_strchr_gnl(line, '\n');
	copy_line = ft_strdup_ex(line);
	if (!ft_strcmp(copy_line, list->inf->file))
	{
		free(line);
		free(copy_line);
		return (0);
	}
	write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
	free(line);
	free(copy_line);
	return (1);
}

void	here_doc(t_data *vars, t_list *list, char *name)
{
	int			fd;
	char		*line;
	int			ret;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		heredoc_err(vars, list);
	ret = 1;
	while (ret == 1)
		ret = hd(list, &fd);
	close(fd);
	//fd = open(name, O_RDONLY);
	//if (fd < 0)
	//	heredoc_err(vars, list);
	//unlink(name);
	exit(0);
}

void	hd_sigint_handler(int s)
{
	//ioctl(0, TIOCSTI, "\n");
	printf("\n");
	//ft_putstr_fd("^C\n", STDOUT_FILENO);
	exit (142);
	// rl_replace_line("", 1);
	// rl_on_new_line();
	// rl_redisplay();
}

void	init_hd_signals(void)
{
	signal(SIGINT, hd_sigint_handler);
}

int	execute_hd(t_list *list, t_data *vars)
{
	int	in_n;
	t_inf *copy;
	int		i;
	char	*name_tmp;
	char	*l_id;
	char	*i_id;
	int		wstatus;

	copy = list->inf;
	in_n = ft_infsize(list->inf);
	i = 1;
	while (in_n != 0 && list->inf != NULL)
	{
		if (list->inf->flag == 'h')
		{
			l_id = ft_itoa(list->list_id);
			i_id = ft_itoa(i);
			name_tmp = ft_strjoin(".heredoc_tmp_", l_id);
			list->inf->hd_name = ft_strjoin(name_tmp, i_id);
			free(l_id);
			free(i_id);
			free(name_tmp);
			vars->id = fork();
			if (vars->id == -1)
				ft_putstr_fd("Error while forking", 2);
			if (vars->id == 0)
			{
				//signal(SIGINT, SIG_DFL);
				init_hd_signals();
				here_doc(vars, list, list->inf->hd_name);
			}
			signal(SIGINT, SIG_IGN);
			waitpid(vars->id, &wstatus, 0);
				if (WIFEXITED(wstatus))
			wstatus = WEXITSTATUS(wstatus);
			init_signals();
			if (wstatus == 142)
				break;
			i++;
		}
		in_n--;
		list->inf = list->inf->next;
	}
	in_n = ft_infsize(list->inf);
	list->inf = copy;
	if (wstatus == 142)
		return (1);
	return (0);
}

void	count_hd(t_list *list)
{
	int	in_n;
	t_inf *copy;

	copy = list->inf;
	in_n = ft_infsize(list->inf);
	while (in_n != 0 && list->inf != NULL)
	{
		if (list->inf->flag == 'h')
			list->hd_nbr++;
		list->inf = list->inf->next;
		in_n--;
	}
	list->inf = copy;
}

int	handle_heredoc(t_list *list, t_data *vars)
{
	t_list	*copy;
	int		i;
	int		flag;

	flag = 0;
	copy = list;
	while (list != NULL)
	{
		count_hd(list);
		if (list->hd_nbr != 0)
				if (execute_hd(list, vars) == 1)
				{
					flag = 1;
					break;
				}
		list = list->next;
	}
	list = copy;
	//printf ("FLAG = %d\n", flag);
	return (flag);
}

void	unlink_heredocs(t_list *list, t_data *vars)
{
	int	in_n;
	t_inf *copy;
	int		i;
	char	*name;

	copy = list->inf;
	in_n = ft_infsize(list->inf);
	i = 1;
	while (in_n != 0 && list->inf != NULL)
	{
		if (list->inf->flag == 'h' && list->inf->hd_name != NULL)
		{
			unlink(list->inf->hd_name);
			i++;
		}
		in_n--;
		list->inf = list->inf->next;
	}
	list->inf = copy;
}
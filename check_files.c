/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:10:56 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/12 14:10:57 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// проверяю файлы. если что не так - выхожу
/*
vars->out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
файлы на инпут, то есть откуда читать. если 
vars->in = open(argv[1], O_RDONLY);
*/

// void	heredoc_err(t_data *vars, t_list *list)
// {
// 	unlink(".heredoc_tmp");
// 	perror("file descriptor error\n");
// 	// FREE all malloced in structure before execution!!!!!!! 
// 	//нужно то что в листе замалочено убрать. временно сделаем это>>
// 	free(list);
// 	free_pipes(vars);
// 	exit(1);
// }

// void	sigint_handler_hd(int sig)
// {
// 	ft_putstr_fd("^C\n", STDOUT_FILENO);
// //	rl_replace_line("", 1);
// //	rl_on_new_line();
// //	rl_redisplay();
// 	(void) sig;
// }

// void	signals_hd(void)
// {
// 	// t_sigaction	act;
// 	// t_sigaction	ign;

// 	// act.sa_flags = SA_RESTART;
// 	// sigemptyset(&act.sa_mask);
// 	// act.sa_handler = &sigint_handler_hd;
// 	// ign.sa_flags = SA_RESTART;
// 	// sigemptyset(&ign.sa_mask);
// 	// ign.sa_handler = SIG_IGN;
// 	// if (sigaction(SIGINT, &act, NULL) != 0)
// 	// 	exit(EXIT_FAILURE);
// 	// if (sigaction(SIGQUIT, &ign, NULL) != 0)
// 	// 	exit(EXIT_FAILURE);
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// int	hd(t_list *list, int *fd)
// {
// 	char	*line;
// 	char	*copy_line;
// 	int		i;

// 	signals_hd();
// 	line = readline("> ");
// 	//signals_hd();
// 	if (line == NULL)
// 	{
// 		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 1);
// 		ft_putstr_fd(list->inf->file, 1);
// 		ft_putstr_fd("')\n", STDOUT_FILENO);
// 		return (0);
// 	}
// 	if (!line)
// 		exit(1);
// 	i = ft_strchr_gnl(line, '\n');
// 	copy_line = ft_strdup_ex(line);
// 	if (!ft_strcmp(copy_line, list->inf->file))
// 	{
// 		free(line);
// 		free(copy_line);
// 		return (0);
// 	}
// 	write(*fd, line, ft_strlen(line));
// 	write(*fd, "\n", 1);
// 	free(line);
// 	free(copy_line);
// 	return (1);
// }

// int	here_doc(t_data *vars, t_list *list)
// {
// 	int			fd;
// 	char		*line;
// 	static char	*buffer;
// 	int			ret;

// 	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd < 0)
// 		heredoc_err(vars, list);
// 	ret = 1;
// 	while (ret == 1)
// 		ret = hd(list, &fd);
// 	free(buffer);
// 	close(fd);
// 	fd = open(".heredoc_tmp", O_RDONLY);
// 	if (fd < 0)
// 		heredoc_err(vars, list);
// 	unlink(".heredoc_tmp");
// 	return (fd);
// }

void	check_out_files(t_list *list, t_data *vars, char ***env)
{
	int	out_n;
	t_outf	*copy;

	copy = list->outf;
	vars->out_file = -2;
	out_n = ft_outfsize(list->outf);
	//rintf("list->inf->file (limiter) = %s", list->inf->file);
	while (out_n != 0 && list->outf != NULL)
	{
		if (list->outf->flag == 'a')
			vars->out_file = open(list->outf->file,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			vars->out_file = open(list->outf->file,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (vars->out_file == -1)
		{
			perror(list->outf->file);
			// FREE all malloced in structure before execution!!!!!!!
			//free_all_main(list, env);
			free_pipes(vars);
			exit (1);
		}
		if (out_n - 1 != 0)
			close(vars->out_file);
		out_n--;
		list->outf = list->outf->next;
	}
	list->outf = copy;
}

//проверяю доступ к файлам. если их нет - создаю. 
void	check_in_files(t_list *list, t_data *vars, char ***env)
{
	int	in_n;
	t_inf *copy;

	copy = list->inf;
	vars->in_file = -2;
	in_n = ft_infsize(list->inf);
	while (in_n != 0 && list->inf != NULL)
	{
		if (list->inf->flag == 'h')
			vars->in_file = open(list->inf->hd_name, O_RDONLY);
		else
		{
			vars->in_file = open(list->inf->file, O_RDONLY);
		}
		if (vars->in_file == -1)
		{
			perror(list->inf->file); // no such file or directory or permission denied message. TEST!!!
			// FREE all malloced in structure before execution!!!!!!!
			//free_all_main(list, env);
			free_pipes(vars);
			exit (1);
		}
		if (in_n - 1 != 0)
			close(vars->in_file);
		in_n--;
		list->inf = list->inf->next;
	}
	list->inf = copy;
	check_out_files(list, vars, env);
}

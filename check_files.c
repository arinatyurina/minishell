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

#include <readline/readline.h>

int	hd(t_list *list, int *fd)
{
	char	*line;
	char	*copy_line;
	int		i;

	line = readline("> ");  // Здесь изменено
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

int	here_doc(t_data *vars, t_list *list)
{
	int			fd;
	char		*line;
	static char	*buffer;
	int			ret;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		heredoc_err(vars, list);
	ret = 1;
	while (ret == 1)
		ret = hd(list, &fd);
	free(buffer);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		heredoc_err(vars, list);
	unlink(".heredoc_tmp");
	return (fd);
}

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
			perror(list->outf->file); // no such file or directory or permission denied message. TEST!!!
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
			vars->in_file = here_doc(vars, list);
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

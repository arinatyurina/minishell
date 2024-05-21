/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:10:14 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/10 11:36:34 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_err(t_data *vars, t_list *list)
{
	unlink(".heredoc_tmp");
	perror("file descriptor error\n");
	free_list(&list);
	free_pipes(vars);
	exit(1);
}

void	ctrl_d_hd(t_list *list)
{
	ft_putstr_fd("minishell: warning: here-document", 1);
	ft_putstr_fd("delimited by end-of-file (wanted `", 1);
	ft_putstr_fd(list->inf->file, 1);
	ft_putstr_fd("')\n", STDOUT_FILENO);
	exit (0);
}

int	hd(t_list *list, int *fd)
{
	char	*line;
	char	*copy_line;
	int		i;

	line = readline("> ");
	if (line == NULL)
		ctrl_d_hd(list);
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
	int			ret;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		heredoc_err(vars, list);
	ret = 1;
	while (ret == 1)
		ret = hd(list, &fd);
	close(fd);
	free_list(&list);
	exit(0);
}

void	unlink_heredocs(t_list *list)
{
	t_list	*list_head;
	t_inf	*copy;

	list_head = list->head;
	list = list->head;
	while (list != NULL)
	{
		copy = list->inf;
		while (list->inf != NULL)
		{
			if (list->inf->flag == 'h' && list->inf->hd_name != NULL)
				unlink(list->inf->hd_name);
			list->inf = list->inf->next;
		}
		list->inf = copy;
		list = list->next;
	}
	list = list_head;
}

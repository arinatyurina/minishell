/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:33:59 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/03 17:09:16 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_sigint_handler(int s)
{
	printf("\n");
	exit (142);
}

void	hd_child(t_list *list, t_data *vars)
{
	signal(SIGINT, hd_sigint_handler);
	here_doc(vars, list, list->inf->hd_name);
}

int	name_heredoc(t_list *list, t_data *vars, int i)
{
	char	*name_tmp;
	char	*l_id;
	char	*i_id;
	int		wstatus;

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
		hd_child(list, vars);
	signal(SIGINT, SIG_IGN);
	waitpid(vars->id, &wstatus, 0);
	if (WIFEXITED(wstatus))
		wstatus = WEXITSTATUS(wstatus);
	init_signals();
	return (wstatus);
}

int	execute_hd(t_list *list, t_data *vars)
{
	int		in_n;
	t_inf	*copy;
	int		i;
	int		wstatus;

	copy = list->inf;
	in_n = ft_infsize(list->inf);
	i = 1;
	while (in_n != 0 && list->inf != NULL)
	{
		if (list->inf->flag == 'h')
		{
			wstatus = name_heredoc(list, vars, i);
			if (wstatus == 142)
				break ;
			i++;
		}
		in_n--;
		list->inf = list->inf->next;
	}
	list->inf = copy;
	if (wstatus == 142)
		return (1);
	return (0);
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
		{
			if (execute_hd(list, vars) == 1)
			{
				flag = 1;
				break ;
			}
		}
		list = list->next;
	}
	list = copy;
	return (flag);
}

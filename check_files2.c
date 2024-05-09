/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:43:07 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 13:45:35 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_outf_null(t_list *list, t_data *vars)
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
		return (1);
	}
	return (0);
}

static int	check_out_files_null(t_list *list, t_data *vars)
{
	int		out_n;
	t_outf	*copy;

	copy = list->outf;
	vars->out_file = -2;
	out_n = ft_outfsize(list->outf);
	while (out_n != 0 && list->outf != NULL)
	{
		if (open_outf_null(list, vars) == 1)
		{
			list->outf = copy;
			return (1);
		}
		if (out_n - 1 != 0)
			close(vars->out_file);
		out_n--;
		list->outf = list->outf->next;
	}
	list->outf = copy;
	return (0);
}

int	check_in_files_null(t_list *list, t_data *vars)
{
	int		in_n;
	t_inf	*copy;

	copy = list->inf;
	in_n = ft_infsize(list->inf);
	while (in_n != 0 && list->inf != NULL)
	{
		if (open_inf_null(list, vars) == 1)
		{
			list->inf = copy;
			return (1);
		}
		if (in_n - 1 != 0)
			close(vars->in_file);
		in_n--;
		list->inf = list->inf->next;
	}
	list->inf = copy;
	return (check_out_files_null(list, vars));
}

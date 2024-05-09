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
	check_out_files(list, vars);
	return (0);
}

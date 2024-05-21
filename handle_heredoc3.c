/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:47:07 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/10 11:47:56 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_hd_name(t_list *list, int i)
{
	char	*name_tmp;
	char	*ret;
	char	*l_id;
	char	*i_id;

	l_id = ft_itoa(list->list_id);
	i_id = ft_itoa(i);
	name_tmp = ft_strjoin(".heredoc_tmp_", l_id);
	ret = ft_strjoin(name_tmp, i_id);
	free(l_id);
	free(i_id);
	free(name_tmp);
	return (ret);
}

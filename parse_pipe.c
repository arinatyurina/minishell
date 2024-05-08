/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:12:27 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 20:26:44 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_pipe(t_list **list, char **tokens, char **env, int *exit_code)
{
	t_list	*next;

	if (((*list)->cmd && *tokens != NULL) || \
		((*list)->inf != NULL) || ((*list)->outf != NULL))
	{
		next = init_list(env);
		add_last_list(list, next);
		return (ft_lstlast(*list));
	}
	else if (*tokens == NULL)
	{
		*exit_code = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	else
	{
		*exit_code = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	return (*list);
}

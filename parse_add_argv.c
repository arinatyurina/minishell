/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:19:02 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 19:45:15 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_existing_argv(t_list **list, char *token)
{
	int		len;
	char	**copy_argv;
	char	**new_argv;

	len = get_num_tokens((*list)->argv);
	new_argv = (char **)malloc((len + 2) * sizeof(char *));
	copy_argv = (*list)->argv;
	while (*copy_argv)
	{
		*new_argv = ft_strdup(*copy_argv);
		new_argv++;
		copy_argv++;
	}
	*new_argv++ = ft_strdup(token);
	*new_argv = NULL;
	free_double_array((*list)->argv);
	(*list)->argv = new_argv - len - 1;
}

void	add_argv(t_list **list, char *token)
{
	char	**new_argv;

	if ((*list)->argv)
		add_existing_argv(list, token);
	else
	{
		new_argv = (char **)malloc(2 * sizeof(char *));
		*new_argv = ft_strdup(token);
		*(new_argv + 1) = NULL;
		(*list)->argv = new_argv;
	}
}

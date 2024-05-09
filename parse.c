/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:57:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 19:51:43 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_single(char *str)
{
	char	*new;

	new = remove_quotes(str);
	return (new);
}

void	parse_string(t_list **list, char *user_input, \
						char **tokens, int *exit_code)
{
	char	*str;

	if (**tokens == '\"')
		str = parse_double(*tokens, (*list)->env, exit_code);
	else if (**tokens == '\'')
		str = parse_single(*tokens);
	else
		str = parse_no_q(*tokens, (*list)->env, exit_code);
	if ((*list)->cmd)
	{
		add_argv(list, str);
	}
	else
		(*list)->cmd = ft_strdup(str);
	free(str);
}

void	set_id_list(t_list **list)
{
	t_list	*temp;
	int		i;

	if (*list != NULL)
	{
		temp = *list;
		i = 1;
		while (temp)
		{
			temp->list_id = i;
			temp = temp->next;
			i++;
		}
	}
}

t_list	*parse(char *user_input, char **tokens, char **env_copy, int *exit_code)
{
	t_list	*list;
	t_list	*current;

	list = init_list(env_copy);
	current = list;
	while (*tokens)
	{
		if (!ft_strcmp(*tokens, ">") || !ft_strcmp(*tokens, "<") || \
			!ft_strcmp(*tokens, ">>") || !ft_strcmp(*tokens, "<<"))
		{
			parse_red(tokens, &current, exit_code);
			if (current == NULL)
				return (NULL);
			tokens++;
		}
		else if (!ft_strcmp(*tokens, "|"))
		{
			current = parse_pipe(&current, tokens + 1, env_copy, exit_code);
			if (current == NULL)
			{
				free_list(&list);
				return (NULL);
			}
		}
		else
			parse_string(&current, user_input, tokens, exit_code);
		tokens++;
	}
	set_id_list(&list);
	return (list);
}

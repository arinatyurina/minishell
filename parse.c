/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:57:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 13:05:24 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_pipe(t_list **list, char **tokens, char **env, int *exit_code)
{
	t_list	*next;

	if ((*list)->cmd && *tokens != NULL)
	{
		next = init_list(env);
		add_last_list(list, next);
		return(ft_lstlast(*list));
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

char	*parse_single(char *str)
{
	char	*new;

	new = remove_quotes(str);
	return (new);
}

int	is_next_string_space(char *token, char *user_input)
{
	char	*ptr;
	char	ch;

	ptr = ft_strnstr(user_input, token, ft_strlen(user_input));
	ch = *(ptr + ft_strlen(token));
	if (is_space(ch))
		return(1);
	return (0);
}

void	add_argv(t_list **list, char *token)
{
	int		len;
	char	**copy_argv;
	char	**new_argv;

	len = 0;
	copy_argv = (*list)->argv;
	if ((*list)->argv)
	{
		while(*copy_argv)
		{
			len++;
			copy_argv++;
		}
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
		copy_argv = (*list)->argv;
		free_double_array(copy_argv);
		(*list)->argv = new_argv - len - 1;
	}
	else 
	{
		new_argv = (char **)malloc(2 * sizeof(char *));
		*new_argv = ft_strdup(token);
		*(new_argv + 1)= NULL;
		(*list)->argv = new_argv;
	}
}

void	parse_string(t_list **list, char *user_input, char **tokens,  int *exit_code)
{
	char	*str;

	if (**tokens == '\"')
	{
		str = parse_double(*tokens, (*list)->env, exit_code);
		if ((*list)->cmd)
		{
			add_argv(list, str);
		}
		else 
			(*list)->cmd = str;
		free(str);
	}
	else if (**tokens == '\'')
	{
		str = parse_single(*tokens);
		if ((*list)->cmd)
		{
			add_argv(list, str);
		}
		else 
			(*list)->cmd = str;
		free(str);
	}
	else 
	{
		str = parse_no_q(*tokens, (*list)->env, exit_code);
		if ((*list)->cmd)
		{
			add_argv(list, str);
		}
		else 
			(*list)->cmd = ft_strdup(str);
		free(str);
	}
}

void set_id_list(t_list **list)
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

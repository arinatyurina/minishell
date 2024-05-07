/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:08:43 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/07 20:13:41 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_env(char *token, char **env, int *exit_code)
{
	char	*value;
	char	*env_word;
	int		len;

	value = NULL;
	len = ft_strlen(token) - 1;
	while (*env && value == NULL)
	{
		env_word = *env;
		if (!ft_strncmp(*env, token + 1, len) && *(env_word + len) == '=')
		{
			value = (char *)malloc((ft_strlen(*env + len + 1) + 1) * sizeof(char));
			ft_strlcpy(value, *env + len + 1, ft_strlen(*env + len + 1) + 1);
		//	value = *env + len + 1;
		}
		else if (!ft_strncmp("$?", token, len + 1))
			value = ft_itoa(*exit_code);
		env++;
	}
	return (value);
}

char	**realloc_tokens(char **tokens, int index, char *value)
{
	int		i;
	int		size;
	char	**new;

	size = get_num_tokens(tokens);
	i = 0;
	new = (char **)malloc((size + 1) * sizeof(char *));
	while (i < size)
	{
		if (index == i)
		{
			new[i] = (char *)malloc((ft_strlen(value) + 1));
			ft_strlcpy(new[i], value, ft_strlen(value) + 1);
		}
		else
		{
			new[i] = (char *)malloc((ft_strlen(tokens[i]) + 1));
			ft_strlcpy(new[i], tokens[i], ft_strlen(tokens[i]) + 1);
		}
		i++;
	}
	new[size] = NULL;
	free_double_array(tokens);
	return (new);
}

char	*get_env_parse(char *word, char **env, int *exit_code)
{
	char	*value;
	char	*env_word;

	value = NULL;
	if (env != NULL)
		value = return_env(word, env, exit_code);
	if (value)
		return (value);
	else
		value = (char *)ft_calloc(1, 1);
	return (value);
}

char	**replace_env(char **tokens, char **env, int *exit_code)
{
	int		num;
	int		i;
	char	*token;
	char	*env_value;

	num = get_num_tokens(tokens);
	i = 0;
	while(i < num)
	{
		token = tokens[i];
		if (*token == '$' && (is_alphanum(*(token + 1)) || *(token + 1) == '?'))
		{
			env_value = get_env_parse(token, env, exit_code);
			tokens = realloc_tokens(tokens, i, env_value);
			free(env_value);
		}
		i++;
	}
	return (tokens);
}
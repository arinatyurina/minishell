/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:45:34 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 18:45:43 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*preparse_string(char *str, char **env, int *exit_code)
{
	char	*ret;

	ret = NULL;
	if (*str == '\"')
		ret = parse_double(str, env, exit_code);
	else if (*str == '\'')
		ret = parse_single(str);
	else 
		ret = parse_no_q(str, env, exit_code);
	return (ret);
}

char	*make_single_q(char **str)
{
	int		len;
	char	*res;
	char	*copy;

	len = ft_strlen(*str);
	res = (char *)malloc((len + 3) * sizeof(char));
	copy = *str;
	*res++ = '\'';
	while (*copy)
		*res++ = *copy++;
	*res++ = '\'';
	*res = '\0';
	free(*str);
	return (res - len - 2);
}

char	*parse_cat(char *first, char *second, char **env, int *exit_code)
{
	char	*parsed_first;
	char	*parsed_second;
	char	*final;

	parsed_first = preparse_string(first, env, exit_code);
	parsed_second = preparse_string(second, env, exit_code);
	final = (char *)ft_calloc((ft_strlen(parsed_first) + ft_strlen(parsed_second) + 1), sizeof(char));
	ft_strlcpy(final, parsed_first, ft_strlen(parsed_first) + 1);
	ft_strlcpy(final + ft_strlen(parsed_first), parsed_second, ft_strlen(parsed_second) + 1);
	final = make_single_q(&final);
	free(parsed_first);
	free(parsed_second);
	return (final);
}

char	**realloc_t_p(char **tokens, int index, char *value)
{
	int		i;
	int		size;
	char	**new;

	size = get_num_tokens(tokens);
	i = 0;
	new = (char **)malloc((size) * sizeof(char *));
	while (i < index)
	{
		new[i] = ft_strdup(tokens[i]);
		i++;
	}
	new[index] = ft_strdup(value);
	free(value);
	i = index + 1;
	while (i < size - 1)
	{
		if (tokens[i + 1] == NULL)
			break;
		new[i] = ft_strdup(tokens[i + 1]);
		i++;
	}
	new[size - 1] = NULL;
	free_double_array(tokens);
	return (new);
}

char	**preparse(char *user_input, char **tokens, \
					 char **env, int *exit_code)
{
	int		i;
	int		index;
	char	*ptr;
	char	*new_token;
	int		num;
	
	i = 1;
	num = get_num_tokens(tokens);
	while (i < num)
	{
		if (tokens[i] == NULL)
			break ;
		if (!is_special_str(tokens[i]))
		{
			ptr = ft_strnstr(user_input, tokens[i], ft_strlen(user_input));
			if (!is_space(*(ptr - 1)))
			{
				if (!is_special_str(tokens[i - 1]))
				{
					new_token = parse_cat(tokens[i - 1], tokens[i], env, exit_code);
					tokens = realloc_t_p(tokens, i - 1, new_token);
					i--;
				}
			}
		}
		i++;
	}
	return (tokens);
}
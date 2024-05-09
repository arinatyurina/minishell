/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:21:34 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 19:44:40 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words_str(char *s)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && is_alphanum(s[i + 1]))
		{
			i++;
			while (is_alphanum(s[i]) && s[i])
				i++;
		}
		else if (s[i] == '$' && s[i + 1] == '?')
			i += 2;
		else if (s[i] == '$')
			i++;
		else
			while (s[i] && !(s[i] == '$' && is_alphanum(s[i + 1])) \
					&& !((s[i] == '$') && (s[i + 1] == '?')))
				i++;
		words++;
	}
	return (words);
}

static int	split_i(char *s, int i)
{
	if (s[i] == '$' && is_alphanum(s[i + 1]))
	{
		i++;
		while (is_alphanum(s[i]) && s[i])
			i++;
	}
	else if (s[i] == '$' && s[i + 1] == '?')
		i += 2;
	else if (s[i] == '$')
		i++;
	else
		while (s[i] && !(s[i] == '$' && is_alphanum(s[i + 1])) \
				&& !((s[i] == '$') && (s[i + 1] == '?')))
			i++;
	return (i);
}

char	**ft_split_str(char *s)
{
	char	**res;
	int		i;
	int		start;

	res = (char **)malloc((ft_count_words_str(s) + 1) * sizeof(char *));
	i = 0;
	while (s[i])
	{
		start = i;
		i = split_i(s, i);
		*res++ = ft_substr(s, start, i - start);
	}
	*res = NULL;
	return (res - ft_count_words_str(s));
}

char	*parse_double(char *str, char **env, int *exit_code)
{
	char	**res;
	int		num;
	char	*final;

	str = remove_quotes(str);
	res = ft_split_str(str);
	res = replace_env(res, env, exit_code);
	num = get_len_tokens(res);
	final = merge_tokens(res);
	free(str);
	free_double_array(res);
	return (final);
}

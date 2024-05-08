/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:27:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 19:09:27 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*subs;
	int		i;

	if (start >= ft_strlen(s))
	{
		subs = ft_calloc(1, sizeof(char));
		if (!subs)
			return (NULL);
		return (subs);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!subs)
		return ((void *)0);
	i = 0;
	while (i < len && s[start + i])
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

char	**split_special(char *s, int *i, char **res)
{
	if (s[*i] == '\'' || s[*i] == '\"')
		res = split_quotes(s, i, res);
	else if (s[*i] == '>' || s[*i] == '<')
		res = split_red(s, i, res);
	else if (s[*i] == '|')
		res = split_pipe(s, i, res);
	else if (s[*i] == '$')
		res = split_exp(s, i, res);
	return (res);
}

char	**split_process(char *s, char **res)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (i <= ft_strlen(s) && s[i] != '\0')
	{
		while (is_space(s[i]))
			i++;
		if (is_special(s[i]))
			res = split_special(s, &i, res);
		else if (!is_space(s[i]))
		{
			start = (int)i;
			while (!is_space(s[i]) && s[i] != '\0' && !is_special(s[i]))
				i++;
			if (i - start > 0)
				*res++ = ft_substr(s, start, i - start);
		}
	}
	return (res);
}

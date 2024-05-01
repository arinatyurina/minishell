/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:30:14 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/18 18:01:11 by rtavabil         ###   ########.fr       */
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

int	is_special(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' \
			|| c == '$' || c == '|');
}

int	is_space(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

char	*count_special(char *s)
{
	if (*s == '\'')
		s = ft_strchr(s + 1, '\'');
	else if (*s == '\"')
		s = ft_strchr(s + 1, '\"');
	else if (*s == '>')
	{
		if (*(s + 1) == '>')
			s = s + 1;
	}
	else if (*s == '<')
	{
		if (*(s + 1) == '<')
			s = s + 1;
	}
	else if (*s == '$')
		;
	return (s);
}

int	ft_count_words(char *s)
{
	int	words;
	int	flag;

	words = 0;
	flag = 0;
	while (*s)
	{
		if (!is_space(*s) && flag == 0 && !is_special(*s))
		{
			flag = 1;
			words++;
		}
		if (is_space(*s) || is_special(*s))
			flag = 0;
		if (is_special(*s))
		{
			s = count_special(s);
			words++;
		}
		s++;
	}
	return (words);
}

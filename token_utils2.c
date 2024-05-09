/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:30:14 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 17:03:29 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	if (c == '$' && !is_alphanum(*(&c + 1)))
		return (0);
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

char	*exp_end(char *s)
{
	if (*s != '\0')
	{
		while (*s)
		{
			if (is_special(*s) || is_space(*s))
				break ;
			s++;
		}
	}
	return (s - 1);
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
		s = exp_end(s + 1);
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

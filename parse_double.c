/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:21:34 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/26 12:27:21 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words_str(char *s, char* lim)
{
	int		words;
	int		flag;
	int		i;
	char	*ptr;
	int		exp;

	words = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '$') && (is_alphanum(s[i + 1])))
		{
			flag = 1;
			words++;
			i++;
		}
		if ((flag == 1) && (!is_alphanum(s[i])))
		{
			flag = 0;
			words++;
		}
		i++;
	}
	return (words);
}

char	**ft_split_str(char *s, char* lim)
{
	char	**res;
	int		i;
	char	*ptr;

	res = (char **)malloc((ft_count_words_str(s, lim) + 1) * sizeof(char *));
	if (!s || !res)
		return ((void *)0);
	i = 0;
	while (*(s + i))
	{
		if (!ft_strncmp(s + i, lim, ft_strlen(lim)) && !is_alphanum(*(s + i + 1)))
		{
			*res++ = ft_substr(s + i, 0, ft_strlen(ptr) - ft_strlen(lim));
			i += ft_strlen(lim);
			
		}
		i++;
	}
	*res = (void *)0;
	return (res - ft_count_words_str(s, lim));
}

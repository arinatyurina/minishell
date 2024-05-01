/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:09:22 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/29 14:15:57 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_sp(char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

void	ft_bzero_sp(void *dest, int byte_sizes)
{
	char	*temp_dest;

	temp_dest = (char *)dest;
	while (byte_sizes--)
		*(temp_dest++) = 0;
}

void	*ft_calloc_sp(int num, int byte_sizes)
{
	void	*result;

	result = malloc(num * byte_sizes);
	if (!result)
		return (NULL);
	ft_bzero_sp(result, num * byte_sizes);
	return (result);
}

char	*ft_substr_sp(char *s, int start, int len)
{
	char	*subs;
	int		i;

	if (start >= ft_strlen_sp(s))
	{
		subs = ft_calloc_sp(1, sizeof(char));
		if (!subs)
			return (NULL);
		return (subs);
	}
	if (ft_strlen_sp(s) - start < len)
		len = ft_strlen_sp(s) - start;
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

static int	ft_count_words_space(char const *s, char c)
{
	int	words;
	int	flag;

	words = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			words++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (words);
}

char	**ft_split_space(char *s, char c)
{
	char	**res;
	int	i;
	int		start;

	res = (char **)malloc((ft_count_words_space(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return ((void *)0);
	i = 0;
	start = -1;
	while (i <= ft_strlen_sp(s) && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c)
		{
			start = (int)i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (i - start > 0)
				*res++ = ft_substr_sp(s, start, i - start);
		}	
	}
	*res = (void *)0;
	return (res - ft_count_words_space(s, c));
}
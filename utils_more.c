/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:32:46 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/11 13:32:59 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_infsize(t_inf *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_outfsize(t_outf *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static int	ft_count_w(char const *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			words++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}

char	*ft_substr_split(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s);
	if (!s)
		return (0);
	if (slen < start)
		len = 0;
	if (len > slen)
		len = slen;
	else if (len > (slen - start))
		len = slen - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (i < len && i < slen)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

char	**ft_split_ex(char *s, char c)
{
	int		i;
	int		start;
	char	**res;

	i = 0;
	start = 0;
	res = (char **)ft_malloc((ft_count_w(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			*res++ = ft_substr_split(s, start, i - start);
			if (!res)
				return (0);
		}
	}
	*res = NULL;
	return (res - ft_count_w(s, c));
}

char	*ft_strjoin_three(char *s1, char ch, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = ch;
	i++;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strndup(char *s1, size_t n)
{
	char *s2;

	if (!(s2 = (char *)malloc(n + 1)))
		return (0);
	ft_memcpy(s2, s1, n);
	s2[n + 1] = 0;
	return (s2);
}

static size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i - 1);
}

char	*ft_itoa(int n)
{
	char		*str_num;
	size_t		digits;
	long int	num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}

void	count_hd(t_list *list)
{
	int		in_n;
	t_inf	*copy;

	copy = list->inf;
	in_n = ft_infsize(list->inf);
	while (in_n != 0 && list->inf != NULL)
	{
		if (list->inf->flag == 'h')
			list->hd_nbr++;
		list->inf = list->inf->next;
		in_n--;
	}
	list->inf = copy;
}
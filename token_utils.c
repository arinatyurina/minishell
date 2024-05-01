/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:28:37 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/29 14:18:36 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *dest, int byte_sizes)
{
	char	*temp_dest;

	temp_dest = (char *)dest;
	while (byte_sizes--)
		*(temp_dest++) = 0;
}

void	*ft_calloc(int num, int byte_sizes)
{
	void	*result;

	result = malloc(num * byte_sizes);
	if (!result)
		return (NULL);
	ft_bzero(result, num * byte_sizes);
	return (result);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == ch)
		return ((char *)s + i);
	return ((char *)0);
}

int	ft_strchrin(char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (s[i] == ch)
		return (i);
	return (-1);
}

int	ft_strlen(char *s)
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

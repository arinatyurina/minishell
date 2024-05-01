/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:14 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/22 15:13:55 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *src)
{
	char	*result;
	int	i;

	i = 0;
	result = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!result)
		return (NULL);
	while (*src)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s2[i] < s1[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strnstr(char *big, char *little, int len)
{
	int	i;

	if (*little == 0)
		return (big);
	i = ft_strlen(little);
	while (*big && i <= len)
	{
		if (*big == *little && ft_strncmp(big, little, i) == 0)
			return (big);
		big++;
		len--;
	}
	return ((void *)0);
}

void	*ft_memcpy(void *dest, void *src, int n)
{
	char	*new_dest;
	char	*new_src;
	int	i;

	new_dest = (char *)dest;
	new_src = (char *)src;
	i = 0;
	while (i < n)
	{
		*(new_dest + i) = *(new_src + i);
		i++;
	}
	return (dest);
}

int	ft_strlcpy(char *dst, char *src, int size)
{
	int	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < size)
	{
		ft_memcpy(dst, src, src_len + 1);
	}
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (src_len);
}

int	ft_strlcat(char *dst, char *src, int size)
{
	int	dst_len;
	int	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	while (*dst)
		dst++;
	return (dst_len + ft_strlcpy(dst, src, size + dst_len));
}
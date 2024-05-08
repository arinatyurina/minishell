/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:45:04 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 19:45:25 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

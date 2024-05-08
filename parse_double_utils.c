/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:00:59 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 19:40:53 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_num_tokens(char **tokens)
{
	char	**copy;
	int		num;

	copy = tokens;
	num = 0;
	while (*copy)
	{
		num ++;
		copy++;
	}
	return (num);
}

int	get_len_tokens(char	**tokens)
{
	char	**copy;
	int		len;

	copy = tokens;
	len = 0;
	while (*copy)
	{
		len += ft_strlen(*copy);
		copy++;
	}
	return (len);
}

char	*merge_tokens(int len, char **tokens)
{
	char	*merged;
	char	**copy_tokens;
	int		size;

	size = get_len_tokens(tokens);
	merged = (char *)ft_calloc(1, (size + 1) * sizeof(char));
	copy_tokens = tokens;
	while (*copy_tokens)
	{
		ft_strlcat(merged, *copy_tokens, ft_strlen(*copy_tokens) + 1);
		copy_tokens++;
	}
	return (merged);
}

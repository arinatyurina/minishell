/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:39:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/03 17:31:44 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split(char *s)
{
	char	**res;

	res = (char **)malloc((ft_count_words(s) + 1) * sizeof(char *));
	if (!s || !res)
		return ((void *)0);
	res = split_process(s, res);
	*res = (void *)0;
	return (res - ft_count_words(s));
}

char	**get_tokens(char *user_input)
{
	char	**tokens;

	if (count_quotes(user_input))
	{
		printf("Odd number of  quotes\n");
		return (NULL);
	}
	tokens = ft_split(user_input);
	return (tokens);
}

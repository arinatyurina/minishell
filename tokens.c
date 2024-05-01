/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:39:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/16 18:46:38 by rtavabil         ###   ########.fr       */
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
	printf("%s\n", user_input);
	tokens = ft_split(user_input);
	return (tokens);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char **table;
// 	char *str = {"|<infile<<<xxx   \t | ||  echo \" hello | world  \"'PATH\'here<<"};
// 	char *str_odd = {" \" check all \" \'  whyy\' meow new"};

// 	char	*user = readline("enter>");
// 	printf("%s\n", user);
// 	if (count_quotes(user))
// 	{
// 		printf("Odd number of  quotes\n");
// 		return (1);
// 	}
// 	printf("_________________________________\n");
// 	table = ft_split(user);
// 	while (*table)
// 	{
// 		printf("%s\n", *table);
// 		table++;
// 	}
// }
//  " check all "
//  0123456789012
// if (s[i] == '\"')
// {
// 	start = i;
// 	i = ft_strchrin(&s[i + 1], '\"');
// 	if (i > 0)
// 		*res++ = ft_substr(s, start, i + 2);
// 	i = start + i + 2;
// }
// else if (s[i] == '\'')
// {
// 	start = i;
// 	i = ft_strchrin(&s[i + 1], '\'');
// 	if (i > 0)
// 		*res++ = ft_substr(s, start, i + 2);
// 	i = start + i + 2;
// }
		// else if (s[i] == '>')
// {
// 	if (s[i + 1] == '>')
// 	{
// 		*res++ = ft_substr(s, i, 2);
// 		i = i + 2;
// 	}
// 	else 
// 	{
// 		*res++ = ft_substr(s, i, 1);
// 		i = i + 1;
// 	}
// }
// else if (s[i] == '<')
// {
// 	if (s[i + 1] == '<')
// 	{
// 		*res++ = ft_substr(s, i, 2);
// 		i = i + 2;
// 	}
// 	else 
// 	{
// 		*res++ = ft_substr(s, i, 1);
// 		i = i + 1;
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:39:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/16 17:28:05 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_quotes(char *s, int *i, char **res)
{
	int	start;

	if (s[*i] == '\"')
	{
		start = *i;
		*i = ft_strchrin(&s[*i + 1], '\"');
		if (i > 0)
			*res++ = ft_substr(s, start, *i + 2);
		*i = start + *i + 2;
	}
	else if (s[*i] == '\'')
	{
		start = *i;
		*i = ft_strchrin(&s[*i + 1], '\'');
		if (*i > 0)
			*res++ = ft_substr(s, start, *i + 2);
		*i = start + *i + 2;
	}
	return (res);
}

char	**split_red(char *s, int *i, char **res)
{
	if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
		{
			*res++ = ft_substr(s, *i, 2);
			*i = *i + 1;
		}
		else
			*res++ = ft_substr(s, *i, 1);
	}
	else if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
		{
			*res++ = ft_substr(s, *i, 2);
			*i = *i + 1;
		}
		else
			*res++ = ft_substr(s, *i, 1);
	}
	*i = *i + 1;
	return (res);
}

char	**split_pipe(char *s, int *i, char **res)
{
	*res++ = ft_substr(s, *i, 1);
	*i = *i + 1;
	return (res);
}

char	**split_process(char *s, char **res)
{
	int		i;
	int		start;

	i = 0;
	start = -1;
	while (i <= ft_strlen(s) && s[i] != '\0')
	{
		while (is_space(s[i]))
			i++;
		if (s[i] == '\'' || s[i] == '\"')
			res = split_quotes(s, &i, res);
		else if (s[i] == '>' || s[i] == '<')
			res = split_red(s, &i, res);
		else if (s[i] == '|')
			res = split_pipe(s, &i, res);
		else if (!is_space(s[i]))
		{
			start = (int)i;
			while (!is_space(s[i]) && s[i] != '\0' && !is_special(s[i]))
				i++;
			if (i - start > 0)
				*res++ = ft_substr(s, start, i - start);
		}
	}
	return (res);
}

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


int	main(int argc, char **argv, char **envp)
{
	char	*user_input;
	t_list	*envp_copy;
	int		exit_status;

	exit_status = 0;
	while (true)
	{
		user_input = readline("minishell:~$ ");
		add_history(user_input);
		//parse(user_input, envp_copy);
		//exec();
	}
	free(user_input);
	rl_clear_history();
}
// int	main(int argc, char **argv, char **envp)
// {
// 	char **table;
// 	char *str = {"|<infile<<<xxx   \t | ||  echo \" hello | world  \"'PATH\'here<<"};
// 	char *str_odd = {" \" ' ' '\"   \"  \' \" \" \" \'\'"};

// 	if (count_quotes(str_odd))
// 	{
// 		printf("Odd number of  quotes\n");
// 		return (1);
// 	}
// 	printf("%s\n", str);
// 	printf("_________________________________\n");
// 	table = ft_split(str);
// 	while (*table)
// 	{
// 		printf("%s\n", *table);
// 		table++;
// 	}
// }

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
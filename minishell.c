/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:30:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 17:08:22 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_env(char **env)
{
	int		len;
	int		i;
	char	**dup_env;

	len = 0;
	i = 0;
	while (env[len] != NULL)
		len++;
	dup_env = malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		dup_env[i] = ft_strdup(env[i]);
		if (dup_env[i] == NULL)
			return (NULL);
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

t_list	*input(char *user_input, char **env_copy, int *exit_code)
{
	char	**tokens;
	t_list	*list;

	list = NULL;
	if (count_quotes(user_input))
	{
		ft_putstr_fd("Odd number of quotes\n", 2);
		*exit_code = 1;
		return (NULL);
	}
	tokens = get_tokens(user_input);
	tokens = preparse(user_input, tokens, env_copy, exit_code);
	list = parse(user_input, tokens, env_copy, exit_code);
	free_double_array(tokens);
	if (list == NULL)
		return (NULL);
	return (list);
}

void	prompt(char **user_input, char ***env_copy, \
 int *exit_status)
{
	t_list	*list;
	while (true)
	{
		*user_input = readline("minishell:~$ ");
		if (*user_input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (!ft_strcmp(*user_input, "") || is_empty_str(*user_input))
			continue ;
		add_history(*user_input);
		list = input(*user_input, *env_copy, exit_status);
		if (list == NULL)
			continue ;
		*exit_status = execute(list, env_copy);
		free_list(&list);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*user_input;
	char	**env_copy;
	int		exit_status;

	init_signals();
	env_copy = duplicate_env(env);
	exit_status = 0;
	prompt(&user_input, &env_copy, &exit_status);
	free(user_input);
	free_dup_env(env_copy);
	rl_clear_history();
}

	// char	*user_input;
	// char	**env_copy;
	// t_list	*list;
	// int		exit_status;

	// init_signals();
	// env_copy = duplicate_env(env);
	// exit_status = 0;
	// while (true)
	// {
	// 	user_input = readline("minishell:~$ ");
	// 	if (user_input == NULL)
	// 	{
	// 		ft_putstr_fd("exit\n", STDOUT_FILENO);
	// 		break;
	// 	}
	// 	if (!ft_strcmp(user_input, "") || is_empty_str(user_input))
	// 		continue;
	// 	add_history(user_input);
	// 	list = input(user_input, env_copy, &exit_status);
	// 	if (list == NULL)
	// 		continue ;
	// 	exit_status = execute(list, &env_copy);
	// 	free_list(&list);
	// }
	// free(user_input);
	// free_dup_env(env_copy);
	// rl_clear_history();
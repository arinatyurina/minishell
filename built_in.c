/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:04:12 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/26 13:51:27 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *cmd, t_list *list, char ***env)
{
	int	i;

	i = 0;
	if ((ft_strcmp(cmd, "echo")) == 0)
		return (ft_echo(list->argv));
	if ((ft_strcmp(cmd, "cd")) == 0)
		return (ft_cd(list->argv, *env));
	if ((ft_strcmp(cmd, "pwd")) == 0)
		return (ft_pwd());
	if ((ft_strcmp(cmd, "export")) == 0)
		return (ft_export(list->argv, env));
	if ((ft_strcmp(cmd, "unset")) == 0)
		return (ft_unset(list->argv, *env));
	if ((ft_strcmp(cmd, "env")) == 0)
		return (ft_env(*env, list->argv));
	if ((ft_strcmp(cmd, "exit")) == 0)
		return (ft_exit(list, env));
	return (1042);
}

// char	**duplicate_env(char **env)
// {
// 	int		len;
// 	int		i;
// 	char	**dup_env;

// 	len = 0;
// 	i = 0;
// 	while (env[len] != NULL)
// 		len++;
// 	dup_env = ft_malloc((len + 1) * sizeof(char *));
// 	while (i < len)
// 	{
// 		dup_env[i] = ft_strdup_ex(env[i]);
// 		if (dup_env[i] == NULL)
// 			return (NULL);
// 		i++;
// 	}
// 	dup_env[i] = NULL;
// 	return (dup_env);
// }

void	free_dup_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

// int	main(int argc, char **list->argv, char **env)
// {
// 	t_data	data;
// 	int		return_value; //remove later

// 	return_value = 10; //remove later
// 	data.env = duplicate_env(env);
// 	if (data.env == NULL)
// 		return (1); //malloc error
// //	ft_env(data.env);
// 	if (argc > 1)
// 		return_value = (builtin(list->argv[1], list->argv + 2, &data));
// //	printf("\nexit code: %i", return_value); //remove later
// //	ft_env(data.env);
// 	free_dup_env(data.env);
// 	return (0);
// }

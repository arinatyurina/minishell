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

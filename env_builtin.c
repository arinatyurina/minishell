/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:43:55 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/28 17:43:56 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env, char **argv)
{
	int	i;

	i = 0;
	if (argv != NULL && argv[0] != NULL)
	{
		ft_putstr_fd("env: ’", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd("’: No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		while (env[i] != NULL)
		{
			if (i != 0)
				ft_putstr_fd("\n", 1);
			ft_putstr_fd(env[i], 1);
			i++;
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}

char	*get_env_value(char **env, char *var, int len)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var, len) != 0)
		i++;
	return (env[i] + (len));
}

int	change_env_var(char **env, char *var, int len, char *new_value)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var, len) != 0)
		i++;
	if (env[i] == NULL)
		return (1);
	else
	{
		free(env[i]);
		env[i] = ft_malloc(len + ft_strlen(new_value) + 1);
		ft_strcpy(env[i], var);
		ft_strlcat(env[i], new_value, len + ft_strlen(new_value) + 1);
		return (0);
	}
}

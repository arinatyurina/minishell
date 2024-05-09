/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:59:28 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/09 20:24:07 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env_var(char **env, char *var, int len)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var, len) != 0)
		i++;
	if (env[i] == NULL || env[i][len] != '=')
		return (1);
	else
	{
		free(env[i]);
		while (env[i] != NULL)
		{
			env[i] = env[i + 1];
			i++;
		}
		return (0);
	}
}

int	ft_unset(char **argv, char **env)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		unset_env_var(env, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (0);
}

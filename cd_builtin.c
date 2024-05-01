/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:13:50 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/26 18:13:59 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
atyurina@c2r6s1:~/minishell$ ./a.out cd
env
Before /home/atyurina/minishell
minishell: cd: Segmentation fault (core dumped)
*/

int	if_cd_luck(char **env)
{
	char	buf[1024];

	if (change_env_var(env, "OLDPWD=", 7, get_env_value(env, "PWD=", 4))
		!= 0)
		return (1);
	if (change_env_var(env, "PWD=", 4, getcwd(buf, sizeof(buf))) != 0)
		return (1);
	return (0);
}

int	cd_home(char **env)
{
	char	*home_env;

	home_env = ft_strjoin("/", get_env_value(env, "HOME=", 5));
	if (chdir(home_env) != 0)
	{
		perror(home_env);
		free(home_env);
		return (1);
	}
	else
	{
		free(home_env);
		if (if_cd_luck(env) == 1)
			return (1);
	}
	return (0);
}

int	cd_with_argv(char **argv, char **env)
{
	if (chdir(argv[0]) != 0)
	{
		if (access(argv[0], F_OK) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else if (access(argv[0], R_OK) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		}
		return (1);
	}
	else
		return (if_cd_luck(env));
	return (0);
}

int	ft_cd(char **argv, char **env)
{
	if (argv[0] != NULL && argv[1] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!argv[0])
	{
		if (cd_home(env) == 1)
			return (1);
	}
	else if (argv[0])
		cd_with_argv(argv, env);
	return (0);
}

/*	for test:
char	s[100];
printf("Before %s\n", getcwd(s, 100)); // printing current working directory 
printf("After: %s\n", getcwd(s, 100)); // printing current working directory 
ft_env(env); //print env 
*/
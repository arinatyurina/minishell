/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:08:26 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/03 13:08:27 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
So, when you exit the shell with exit -30, the exit status becomes 226,
and when you exit with exit -40, the exit status becomes 216.
This behavior is because the exit status 
in Unix-like systems is represented by an 8-bit value, 
allowing a range from 0 to 255. 
Any value outside this range wraps around modulo 256, 
resulting in the observed exit status codes.*/
#include "minishell.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	is_sign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	else
		return (0);
}

void	check_argv_exit(t_list *list, int exit_val, char ***env)
{
	int	i;

	i = 0;
	while (list->argv[0][i] != '\0')
	{
		while (is_space(list->argv[0][i]) == 1)
			i++;
		if (is_sign(list->argv[0][i]) == 1)
			i++;
		while (is_digit(list->argv[0][i]) == 1)
			i++;
		while (is_space(list->argv[0][i]) == 1)
			i++;
		if (list->argv[0][i] != '\0')
		{
			ft_putstr_fd("exit\nbash: exit: ", STDERR_FILENO);
			ft_putstr_fd(list->argv[0], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_val = 2;
			free_dup_env(*env); //instead of this free all!!!!!!!!!!!!!
			// free(list->argv); //!!!
			// free(list); // !!!
			exit (2);
		}
	}
}

int	ft_exit(t_list *list, char ***env)
{
	int	exit_val;

	exit_val = 0; /// EXIT VALUE BY DEFAULT. should it be 0 ?
	//FREE everything... !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (list->argv != NULL && list->argv[0] != NULL && list->argv[1] != NULL)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		exit_val = 2;
		exit (2);
	}
	if (list->argv != NULL && list->argv[0] == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit_val = EXIT_SUCCESS;
	}
	else if (list->argv != NULL && list->argv[0] != NULL)
	{
		check_argv_exit(list, exit_val, env);
		exit_val = ft_atoi(list->argv[0]);
		if (exit_val < 0)
			exit_val = 256 + exit_val % 256;
		else if (exit_val > 255)
			exit_val = exit_val % 256;
	}
	free_dup_env(*env); //instead of this free all!!!!!!!!
	// free(list->argv); //!!!
	// free(list); // !!!
	exit (exit_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:54:56 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/01 14:54:58 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	i;

	i = 0;
	if (argv[0] != NULL && ft_strcmp(argv[0], "-n") == 0)
	{
		while (argv[i + 1] != NULL)
		{
			ft_putstr_fd(argv[i + 1], STDOUT_FILENO);
			if (argv[i + 2] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		while (argv[i] != NULL)
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (argv[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_managing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:04:45 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/12 18:04:56 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_stream(int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
}

void	redirect_back(t_data *vars)
{
	dup2(vars->stdin_og, STDIN_FILENO);
	dup2(vars->stdout_og, STDOUT_FILENO);
}

void	closing_pipes(t_data *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipes_nbr)
	{
		close(vars->pipefd[i][0]);
		close(vars->pipefd[i][1]);
		i++;
	}
}

void	create_pipes(t_data *vars)
{
	int	i;

	vars->pipes_nbr = vars->lists_nbr - 1;
	vars->pipefd = (int **)ft_malloc((vars->pipes_nbr) * sizeof(int *));
	i = 0;
	while (i < vars->pipes_nbr)
	{
		vars->pipefd[i] = (int *)ft_malloc(2 * sizeof(int));
		if (pipe(vars->pipefd[i]) == -1)
			ft_putstr_fd("Error while creating a pipe", 2);
		i++;
	}
}

void	free_pipes(t_data *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipes_nbr)
	{
		free(vars->pipefd[i]);
		i++;
	}
	free(vars->pipefd);
}

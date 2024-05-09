/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:51:44 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/09 17:25:00 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forking(t_list *list, t_data *vars, char ***env)
{
	int	i;

	i = 0;
	while (i < vars->lists_nbr && list != NULL)
	{
		vars->id = fork();
		if (vars->id == -1)
			ft_putstr_fd("Error while forking", 2);
		if (vars->id == 0)
		{
			signals_to_default();
			check_in_files(list, vars);
			check_redirections(vars, list);
			redirect_stream(vars->in_file, vars->out_file);
			closing_pipes(vars);
			now_execute(vars, list, env);
		}
		i++;
		list = list->next;
	}
}

int	one_cmd_builtin(char *cmd, t_data *vars)
{
	if (vars->lists_nbr == 1)
	{
		if (((ft_strcmp(cmd, "echo")) == 0)
			|| ((ft_strcmp(cmd, "cd")) == 0)
			|| ((ft_strcmp(cmd, "pwd")) == 0)
			|| ((ft_strcmp(cmd, "export")) == 0)
			|| ((ft_strcmp(cmd, "unset")) == 0)
			|| ((ft_strcmp(cmd, "env")) == 0)
			|| ((ft_strcmp(cmd, "exit")) == 0))
			return (1);
	}
	return (0);
}

void	case_with_pipes(t_list *list, t_data *vars, char **env)
{
	create_pipes(vars);
	forking(list, vars, &env);
	closing_pipes(vars);
	free_pipes(vars);
}

int	execute_one_builtin(t_list *list, t_data *vars, char ***env)
{
	int	wstatus;

	check_in_files(list, vars);
	check_redirections(vars, list);
	redirect_stream(vars->in_file, vars->out_file);
	wstatus = builtin(list->cmd, list, env);
	redirect_back(vars);
	return (wstatus);
}

int	execute(t_list *list, char ***env)
{
	t_data	vars;
	int		wstatus;

	wstatus = 0;
	vars.lists_nbr = ft_lstsize(list);
	vars.stdin_og = dup(STDIN_FILENO);
	vars.stdout_og = dup(STDOUT_FILENO);
	if (handle_heredoc(list, &vars) == 1)
	{
		unlink_heredocs(list, &vars);
		return (130);
	}
	if (list->cmd == NULL && list->next == NULL)
		return (check_in_files_null(list, &vars));
	if (one_cmd_builtin(list->cmd, &vars) == 1)
		wstatus = execute_one_builtin(list, &vars, env);
	else
	{
		case_with_pipes(list, &vars, *env);
		wstatus = waiting(list, &vars);
	}
	unlink_heredocs(list, &vars);
	return (wstatus);
}

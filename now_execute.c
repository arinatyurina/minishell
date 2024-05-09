/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   now_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:25:54 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/09 17:40:59 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_path_null(t_data *vars, t_list *list, char ***env)
{
	if (vars->path == NULL)
	{
		perror(list->cmd);
		free_pipes(vars);
		free_list(&list);
		free_dup_env(*env);
		rl_clear_history();
		exit (127);
	}
}

// -2 - это флаг, который проверяет 
// есть ли у нас какие то redirection. 
// если есть - то их и оставляем. 
// если нет, то подставляем пайпы или стдин/стдаут
void	check_redirections(t_data *vars, t_list *list)
{
	if (vars->in_file == -2)
	{
		if (list->list_id == 1)
			vars->in_file = STDIN_FILENO;
		else
			vars->in_file = vars->pipefd[list->list_id - 2][0];
	}
	if (vars->out_file == -2)
	{
		if (list->list_id == vars->lists_nbr)
			vars->out_file = STDOUT_FILENO;
		else
			vars->out_file = vars->pipefd[list->list_id - 1][1];
	}
}

char	**ft_executable(char *cmd, char **argv)
{
	char	**exec;
	int		len;
	int		j;
	int		i;

	i = 1;
	j = 0;
	len = 0;
	while (argv != NULL && argv[len] != NULL)
		len++;
	exec = (char **)ft_malloc((len + 2) * sizeof(char *));
	exec[0] = ft_strdup_ex(cmd);
	free(cmd);
	while (argv != NULL && argv[j] != NULL)
	{
		exec[i] = ft_strdup_ex(argv[j]);
		i++;
		j++;
		free(argv[j]);
	}
	exec[i] = NULL;
	return (exec);
}

// 84 line: чистим же среду при форках? т.к. это child, чтобы не было ликов
void	now_execute(t_data *vars, t_list *list, char ***env)
{
	int		return_builtin;
	char	**exec;

	if (list->cmd == NULL)
	{
		ft_putstr_fd("ya zdes\n", 2);
		free_pipes(vars);
		free_list(&list);
		free_dup_env(*env);
		exit (1);
	}
	return_builtin = builtin(list->cmd, list, env);
	if (return_builtin != 1042)
	{
		free_pipes(vars);
		free_list(&list);
		free_dup_env(*env);
		exit (return_builtin);
	}
	checking_access(vars, list, *env);
	if_path_null(vars, list, env);
	exec = ft_executable(list->cmd, list->argv);
	if (execve(vars->path, exec, *env) == -1)
	{
		perror(vars->path);
		free_pipes(vars);
		free(vars->path);
		free_list(&list);
		free_dup_env(*env);
		rl_clear_history();
		free_double_array(exec);
		exit (1);
	}
}

// cmd1 | cmd2 | cmd3
// executed in order
// send out to next pipe. receive in from previous input/
// 1 - не из пайма
// последняя = не в пайп, а в стдаут
// exit code of last one only matters!
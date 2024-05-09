/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:10:56 by atyurina          #+#    #+#             */
/*   Updated: 2024/05/09 18:03:42 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// проверяю файлы. если что не так - выхожу
/*
vars->out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
файлы на инпут, то есть откуда читать. если 
vars->in = open(argv[1], O_RDONLY);
*/

void	open_outf(t_list *list, t_data *vars, t_outf *copy)
{
	if (list->outf->flag == 'a')
		vars->out_file = open(list->outf->file,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		vars->out_file = open(list->outf->file,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (vars->out_file == -1)
	{
		perror(list->outf->file);
		list->outf = copy;
		free_list(&list);
		free_pipes(vars);
		exit (1);
	}
}

void	check_out_files(t_list *list, t_data *vars)
{
	int		out_n;
	t_outf	*copy;

	copy = list->outf;
	vars->out_file = -2;
	out_n = ft_outfsize(list->outf);
	while (out_n != 0 && list->outf != NULL)
	{
		open_outf(list, vars, copy);
		if (out_n - 1 != 0)
			close(vars->out_file);
		out_n--;
		list->outf = list->outf->next;
	}
	list->outf = copy;
}

void	open_inf(t_list *list, t_data *vars, t_inf *copy)
{
	if (list->inf->flag == 'h')
		vars->in_file = open(list->inf->hd_name, O_RDONLY);
	else
		vars->in_file = open(list->inf->file, O_RDONLY);
	if (vars->in_file == -1)
	{
		perror(list->inf->file);
		list-> inf = copy;
		free_list(&list);
		free_pipes(vars);
		exit (1);
	}
}

void	check_in_files(t_list *list, t_data *vars)
{
	int		in_n;
	t_inf	*copy;

	copy = list->inf;
	vars->in_file = -2;
	in_n = ft_infsize(list->inf);
	while (in_n != 0 && list->inf != NULL)
	{
		open_inf(list, vars, copy);
		if (in_n - 1 != 0)
			close(vars->in_file);
		in_n--;
		list->inf = list->inf->next;
	}
	list->inf = copy;
	check_out_files(list, vars);
}

/*
int	open_inf_null(t_list *list, t_data *vars)
{
	if (list->inf->flag == 'h')
		vars->in_file = open(list->inf->hd_name, O_RDONLY);
	else
		vars->in_file = open(list->inf->file, O_RDONLY);
	if (vars->in_file == -1)
	{
		perror(list->inf->file);
		//free_list(&list);
		//free_pipes(vars);
		return (1);
	}
	return (0);
}
*/

int	open_inf_null(t_list *list, t_data *vars)
{
	if (list->inf->flag == 'h')
		vars->in_file = open(list->inf->hd_name, O_RDONLY);
	else
		vars->in_file = open(list->inf->file, O_RDONLY);
	if (vars->in_file == -1)
	{
		perror(list->inf->file);
		return (1);
	}
	return (0);
}

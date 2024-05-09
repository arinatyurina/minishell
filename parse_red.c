/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:05:37 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 14:03:21 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_next_inf(t_list **list, char *file, char *flag)
{
	char	inf_flag;
	t_inf	*infile;

	inf_flag = 'c';
	if (!ft_strcmp(flag, "<<"))
		inf_flag = 'h';
	infile = init_inf(file, inf_flag);
	add_last_inf(&((*list)->inf), infile);
}

void	add_next_outf(t_list **list, char *file, char *flag)
{
	char	out_flag;
	t_outf	*outfile;

	out_flag = 'c';
	if (!ft_strcmp(flag, ">>"))
		out_flag = 'a';
	outfile = init_outf(file, out_flag);
	add_last_outf(&((*list)->outf), outfile);
}

void	parse_red(char **tokens, t_list **list, int *exit_code)
{
	if (!ft_strcmp(*tokens, "<") || !ft_strcmp(*tokens, "<<"))
	{
		if (!is_special_str(*(tokens + 1)) && *tokens && *(tokens + 1))
			add_next_inf(list, *(tokens + 1), *tokens);
		else
		{
			*exit_code = 1;
			ft_putstr_fd("Redirect error, encouneterd special symbol\n", 2);
			list = NULL;
		}
	}
	if (!ft_strcmp(*tokens, ">") || !ft_strcmp(*tokens, ">>"))
	{
		if (!is_special_str(*(tokens + 1)) && *tokens && *(tokens + 1))
			add_next_outf(list, *(tokens + 1), *tokens);
		else
		{
			*exit_code = 1;
			ft_putstr_fd("Redirect error, encouneterd special symbol\n", 2);
			list = NULL;
		}
	}
}

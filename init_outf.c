/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:11:06 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/07 13:13:53 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_outf	*init_outf(char	*file, char flag)
{
	t_outf	*outf;

	outf = malloc(sizeof(t_outf));
	if (!outf)
		return (NULL);
	outf->flag = flag;
	outf->file = ft_strdup(file);
	outf->next = NULL;
	return (outf);
}

t_outf	*ft_lstoutf(t_outf *outf)
{
	if (!outf)
		return (NULL);
	while (outf->next)
		outf = outf->next;
	return (outf);
}

void	add_last_outf(t_outf **head, t_outf *outf)
{
	t_outf	*node;

	if (!outf)
		return ;
	if (!*head)
	{
		*head = outf;
		return ;
	}
	node = ft_lstoutf(*head);
	node->next = outf;
}

void	ft_del_outf(t_outf *outf)
{
	if (!outf)
		return ;
	if (outf->file != NULL)
		free(outf->file);
	free(outf);
}

void	ft_clear_outf(t_outf **outf)
{
	t_outf	*node;

	if (!outf)
		return ;
	while (*outf)
	{
		node = (*outf)->next;
		ft_del_outf(*outf);
		*outf = node;
	}
	outf = NULL;
}


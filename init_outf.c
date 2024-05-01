/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:11:06 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/19 15:21:40 by rtavabil         ###   ########.fr       */
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
	outf->file = file;
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
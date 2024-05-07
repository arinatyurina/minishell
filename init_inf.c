/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:34:46 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/07 13:11:21 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inf	*init_inf(char	*file, char flag)
{
	t_inf	*inf;

	inf = malloc(sizeof(t_inf));
	if (!inf)
		return (NULL);
	inf->flag = flag;
	inf->file = ft_strdup(file);
	inf->next = NULL;
	inf->hd_name = NULL;
	return (inf);
}

t_inf	*ft_lstinf(t_inf *inf)
{
	if (!inf)
		return (NULL);
	while (inf->next)
		inf = inf->next;
	return (inf);
}

void	add_last_inf(t_inf **head, t_inf *inf)
{
	t_inf	*node;

	if (!inf)
		return ;
	if (!*head)
	{
		*head = inf;
		return ;
	}
	node = ft_lstinf(*head);
	node->next = inf;
}

void	ft_del_inf(t_inf *inf)
{
	if (!inf)
		return ;
	if (inf->file != NULL)
		free(inf->file);
	if (inf->hd_name != NULL)
		free(inf->hd_name);
	free(inf);
}

void	ft_clear_inf(t_inf **inf)
{
	t_inf	*node;

	if (!inf)
		return ;
	while (*inf)
	{
		node = (*inf)->next;
		ft_del_inf(*inf);
		*inf = node;
	}
	inf = NULL;
}

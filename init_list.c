/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:14:01 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/23 13:01:40 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_list(char **env_copy)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return(NULL);
	list->list_id = -1;
	list->cmd = NULL;
	list->argv = NULL;
	list->env = env_copy;
	list->inf = NULL;
	list->outf = NULL;
	list->next = NULL;
	return (list);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_last_list(t_list **head, t_list *last)
{
	t_list	*node;

	if (!last)
		return ;
	if (!*head)
	{
		*head = last;
		return ;
	}
	node = ft_lstlast(*head);
	node->next = last;
}

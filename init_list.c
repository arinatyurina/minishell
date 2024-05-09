/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:14:01 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 19:06:21 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_list(char **env_copy, t_list *head)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->list_id = -1;
	list->cmd = NULL;
	list->argv = NULL;
	list->env = env_copy;
	list->inf = NULL;
	list->outf = NULL;
	list->next = NULL;
	list->hd_nbr = 0;
	if (head == NULL)
		list->head = list;
	else
		list->head = head;
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

void	free_list_node(t_list **list)
{
	if (*list && list)
	{
		if ((*list)->cmd != NULL)
			free((*list)->cmd);
		if ((*list)->argv != NULL)
			free_double_array((*list)->argv);
		if ((*list)->inf != NULL)
			ft_clear_inf(&(*list)->inf);
		if ((*list)->outf != NULL)
			ft_clear_outf(&(*list)->outf);
		free(*list);
	}
}

void	free_list(t_list **list)
{
	t_list	*node;

	if (!list)
		return ;
	if ((*list)->list_id != 1)
		*list = (*list)->head;
	while (*list)
	{
		node = (*list)->next;
		free_list_node(list);
		*list = node;
	}
	list = NULL;
}

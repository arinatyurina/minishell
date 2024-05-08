/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:30:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/08 13:43:42 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_inf(t_list *list)
{
	t_inf	*inf;

	inf = list->inf;
	while (inf)
	{
		printf("|%s %c|", inf->file, inf->flag);
		inf = inf->next;
	}
	printf("\n");
}

void	print_outf(t_list *list)
{
	t_outf	*outf;

	outf = list->outf;
	while (outf)
	{
		printf("|%s %c|", outf->file, outf->flag);
		outf = outf->next;
	}
	printf("\n");
}

void	output_list(t_list *list)
{
	char	**argv;
	int		i;
	t_list	*copy;

	i = 0;
	copy = list;
	while (copy)
	{
		printf("___________________________\n");
		printf("LIST NUMBER %d\n", i);
		printf("cmd = %s\n", copy->cmd);
		printf("argv = ");
		argv = copy->argv;
		while (*argv)
		{
			printf("%s ", *argv);
			argv++;
		}
		printf("\n");
		printf("inf are ");
		print_inf(copy);
		printf("outf are ");
		print_outf(copy);
		copy = copy->next;
		i++;
		printf("___________________________\n");
	}
}

char	**duplicate_env(char **env)
{
	int		len;
	int		i;
	char	**dup_env;

	len = 0;
	i = 0;
	while (env[len] != NULL)
		len++;
	dup_env = malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		dup_env[i] = ft_strdup(env[i]);
		if (dup_env[i] == NULL)
			return (NULL);//malloc error
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

t_list	*input(char *user_input, char **env_copy, int *exit_code)
{
	char	**tokens;
	// char	**copy_tokens;
	// int		i;
	t_list	*list;

	list = NULL;
	if (count_quotes(user_input))
	{
		ft_putstr_fd("Odd number of quotes\n", 2);
		*exit_code = 1;
		return (NULL);
	}
	tokens = get_tokens(user_input);
	//tokens = preparse(user_input, tokens, env_copy, exit_code);
	// copy_tokens = tokens;
	// i = 0;
	// while(*copy_tokens)
	// {
	// 	printf("token n0 %d is |%s|\n", i, *copy_tokens);
	// 	i++;
	// 	copy_tokens++;
	// }
	list = parse(user_input, tokens, env_copy, exit_code);
	free_double_array(tokens);
	if (list == NULL)
		return (NULL);
	return(list);
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
	t_list *node;

	if (!list)
		return ;
	while (*list)
	{
		node = (*list)->next;
		free_list_node(list);
		*list = node;
	}
	list = NULL;
}

int	main(int argc, char **argv, char **env)
{
	char	*user_input;
	char	**env_copy;
	t_list	*list;
	int		exit_status;

	init_signals();
	env_copy = duplicate_env(env);
	exit_status = 0;
	while (true)
	{
		user_input = readline("minishell:~$ ");
		if (user_input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break;
		}
		if (!ft_strcmp(user_input, "") || is_empty_str(user_input))
			continue;
		add_history(user_input);
		list = input(user_input, env_copy, &exit_status);
		if (list == NULL)
			continue ;
		exit_status = execute(list, &env_copy);
		free_list(&list);
	}
	free(user_input);
	free_dup_env(env_copy);
	rl_clear_history();
}
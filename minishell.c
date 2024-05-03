/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:30:52 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/03 16:43:54 by rtavabil         ###   ########.fr       */
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

t_list	*input(char *user_input, char **env_copy)
{
	char	**tokens;
	t_list	*list;

	list = NULL;
	tokens = get_tokens(user_input);
	list = parse(user_input, tokens, env_copy);
	return(list);
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
		if (!ft_strcmp(user_input, ""))
			continue;
		add_history(user_input);
		list = input(user_input, env_copy);
		//output_list(list);
		execute(list, &env);
		//exit_status = exec(&env_copy);
	}
	free(user_input);
	//free env_copy
	rl_clear_history();
}
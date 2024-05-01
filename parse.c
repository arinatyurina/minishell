/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:57:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/29 18:00:19 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_str(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, "|"))
		return (1);
	if (!ft_strcmp(str, "$"))
		return (1);
	return (0);
}

void	add_next_inf(t_list **list, char *file, char *flag)
{
	char	inf_flag;
	t_inf	*infile;
	//todo
	//init inf
	//set value and flag
	//add last list->inf
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
	//todo
	//init outf
	//set value and flag
	//add last list->outf
	out_flag = 'c';
	if (!ft_strcmp(flag, ">>"))
		out_flag = 'a';
	outfile = init_outf(file, out_flag);
	add_last_outf(&((*list)->outf), outfile);
}

void	parse_red(char **tokens, t_list **list)
{
	//printf("entered parse_red");
	//printf(" check list %s\n", *(*list)->env);
	if (!ft_strcmp(*tokens, "<") || !ft_strcmp(*tokens, "<<"))
	{
		if (!is_special_str(*(tokens + 1)) && *tokens)
			add_next_inf(list, *(tokens + 1), *tokens);
		// else
		// 	redirect_error(); //TODO syntax error near unexpected token [*(tokens + 1)] 
	}
	if (!ft_strcmp(*tokens, ">") || !ft_strcmp(*tokens, ">>"))
	{
		if (!is_special_str(*(tokens + 1)) && *tokens)
			add_next_outf(list, *(tokens + 1), *tokens);
		// else
		// 	redirect_error(); //TODO syntax error near unexpected token [*(tokens + 1)]
	}
}

t_list	*parse_pipe(t_list **list, char **tokens, char **env)
{
	t_list	*next;
	//TODO
	//check if list has a command 
	//if not 
	//pipe_error() syntax error near unexpected token `|'
	//check if tokens has something after (not pipe)
	//if not
	//pipe_error() syntax error near unexpected token `|'
	//create new t_list instance
	//return list instance

	if ((*list)->cmd)
	{
		next = init_list(env);
		add_last_list(list, next);
		return(ft_lstlast(*list));
	}
	else if (*tokens == NULL)
	{
		//ouput error
	}
	else
	{
		//ouput error 
	}
	return (*list);
}

void	parse_exp(t_list **list, char **tokens, \
				char *user_input, char **env)
{
	//check if space after
	//if not concatenate with next 
	//if next is ''
	//expand /0 /a /b /t /n /v /f /r
	return ;
}


char	*parse_no_q()
{
	//check if next is ' or " or $
	//if yes check for space 
	//if no space concatenate
	//return as it is?
	return (NULL);
}

int	is_alphanum(char c)
{
	if (((c >= 48) && (c <= 57)) || ((c >=97 && c <= 122)) \
		|| (c == '_') || ((c >= 65) && (c <= 90)))
		return (1);
	return (0);
}

char	*find_env_var(char	*key, char **env)
{
	char	*env_var;

	env_var = NULL;
	if (env != NULL)
	{
		while (*env && env_var == NULL)
		{
			if (!ft_strncmp(*env, key, ft_strlen(key)))
				env_var = *env + ft_strlen(key) + 1;
			env++;
		}
	}
	return(env_var);
}

char	*parse_double(char *token, char **env)
{
	int		i;
	int		start;
	char	*parsed;
	char	*env_key;
	int		len;
	char	*env_var;

	start = -1;
	env_key = NULL;
	env_var = NULL;
	if (ft_strchrin(token, '$') != -1)
	{
		printf("entered parse_double() if\n");
		start = ft_strchrin(token, '$') + 1;
		i = start + 1;
		while (token[i])
		{
			if (!is_alphanum(token[i]))
				break;
			i++;
		}
		if (i - start > 1)
		{
			printf("entered parse_double() if() if()\n");
			env_key = ft_substr(token, start, i - start);
			printf("env_char is %s\n", env_key);
		}
		env_var = find_env_var(env_key, env);
		printf("env_var is %s\n", env_var);
		if (env_var == NULL)
			return ("\0");

	}
	// if (env_char)
	// {
	// 	len = ft_strlen(token) - 3 + ft_strlen(env_char);
	// 	parsed = (char *)malloc((len + 1) * sizeof(char));
	// 	if (!parsed)
	// 		return (NULL);
	// 	env_var = 
	// }
	
	//remove quotes
	//-assign new memory
	//-substr from 1 to len - 1
	//free old one
	//check for $ sign
	//if yes expand 
	return (parsed);
}

char	*parse_single()
{
	//remove quotes
	//-assign new memory
	//-substr from 1 to len - 1
	//free old one
	//check for $ sign
	//if yes expand 
	return (NULL);
}

int	is_next_string_space(char *token, char *user_input)
{
	char	*ptr;
	char	ch;

	ptr = ft_strnstr(user_input, token, ft_strlen(user_input));
	ch = *(ptr + ft_strlen(token));
	if (is_space(ch))
		return(1);
	return (0);
}

// char	*return_string(t_list **list, char *user_input, char ***tokens)
// {
// 	char	*token;
// 	char	**temp;

// 	temp = *tokens;
// 	token = NULL;
// 	if (**temp == '\"')
// 	{
// 		printf("token is %s\n", *temp);
// 		token = parse_double(*temp, (*list)->env);
// 	}
// 	else if (*user_input == '\'')
// 		token = parse_single();
// 	else
// 		token = parse_no_q();
// 	// if ((*tokens + 1) && !is_special_str(*(*tokens + 1)))
// 	// {
// 	// 	temp = *tokens + 1;
// 	// 	next = return_string(list, user_input, &temp);
// 	// 	ptr = ft_strnstr(user_input, next, ft_strlen(next));
// 	// 	if (is_space(*(ptr + ft_strlen(*(*tokens + 1)))))
// 	// 	{
// 	// 		next = return_string(list, user_input, tokens);
// 	// 		(*tokens)++;
			
// 	// 		//increment tokens
// 	// 		//concatenate with token
// 	// 	}
// 	// }
// 	// //check if it has space in user input
// 	// //if not and if next token is string -> concatenate with next

// 	// //check $ sign
// 	return (token);
// }

// void	temp_set_cmd(t_list **list, char *user_input)
// {
// 	char	**res;

// 	res = ft_split_space(user_input, ' ');
// 	(*list)->cmd = *res;
// 	(*list)->argv = res + 1;
// }

void	free_double_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	add_argv(t_list **list, char *token)
{
	int		len;
	char	**copy_argv;
	char	**new_argv;

	len = 0;
	copy_argv = (*list)->argv;
	if ((*list)->argv)
	{
		while(*copy_argv)
		{
			len++;
			copy_argv++;
		}
		new_argv = (char **)malloc((len + 2) * sizeof(char *));
		copy_argv = (*list)->argv;
		while (*copy_argv)
		{
			*new_argv = ft_strdup(*copy_argv);
			new_argv++;
			copy_argv++;
		}
		*new_argv++ = token;
		*new_argv = NULL;
		copy_argv = (*list)->argv;
		free_double_array(copy_argv);
		(*list)->argv = new_argv - len - 1;
	}
	else 
	{
		new_argv = (char **)malloc(2 * sizeof(char *));
		*new_argv = token;
		*(new_argv + 1)= NULL;
		(*list)->argv = new_argv;
	}
}

void	parse_string(t_list **list, char *user_input, char **tokens)
{
	//TODO
	//char	*str;
	if ((*list)->cmd)
	{
		add_argv(list, *tokens);
	}
	else 
		(*list)->cmd = *tokens;

	// if (str)
	// 	argv_add((*list)->argv, str); //TODO
	//printf("check args %s\n", *(*list)->argv);

}

void set_id_list(t_list **list)
{
 t_list *temp;
 int  i;

 if (*list != NULL)
 {
  temp = *list;
  i = 1;
  while (temp)
  {
   temp->list_id = i;
   temp = temp->next;
   i++;
  }
 }
}

t_list	*parse(char *user_input, char **tokens, char **env_copy)
{
	t_list	*list;
	t_list	*current;

	//printf("entered parse()\n");
	list = init_list(env_copy);
	current = list;
	//parse_string(&list, user_input, &tokens);
	while (*tokens)
	{
		//printf("entered while\n");
		if (!ft_strcmp(*tokens, ">") || !ft_strcmp(*tokens, "<") || \
			!ft_strcmp(*tokens, ">>") || !ft_strcmp(*tokens, "<<"))
			{
			//	printf("passed if\n");
				parse_red(tokens, &current);
				tokens++;
			}
		else if (!ft_strcmp(*tokens, "|"))
			current = parse_pipe(&current, tokens + 1, env_copy);
		// //make all function return value for outputting errors
		// if (!ft_strcmp(*tokens, "$"))
		// 	parse_exp(&current, tokens, user_input, env_copy);
		else 
			parse_string(&current, user_input, tokens);
		tokens++;
	}
	//printf("finished parse()\n");
	set_id_list(&list);
	return (list);
}


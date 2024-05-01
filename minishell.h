/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:23:44 by rtavabil          #+#    #+#             */
/*   Updated: 2024/04/29 16:17:03 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf, readline
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h> //write, access, open, close, fork, getcwd
# include <stdlib.h> //malloc, free, NULL
# include <sys/types.h> //pid_t
# include <sys/wait.h> //wait
# include <stdbool.h> //booleans
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**env;
	int		exit_val;
	int		lists_nbr;
	int		pipes_nbr;
	int		**pipefd;
	int		in_file;
	int		out_file;
	int		id;
	char	**paths;
	char	*path;
	int		stdout_og;
	int		stdin_og;
}		t_data;

typedef enum e_builtins {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtins;

typedef struct s_inf
{
	char			flag; // 'h' 'c' 
	char			*file;
	struct s_inf	*next;
}	t_inf;

typedef struct s_outf
{
	char			flag; // 'a' 'c'
	char			*file;
	struct s_outf	*next;
}   t_outf;

// list structure:
typedef struct s_list
{
	int				list_id;
	char			*cmd;
	char			**argv;
	char			**env;
	t_inf			*inf;
	t_outf			*outf;
	struct s_list	*next;
}		t_list;

// temporary!!!! for freeinf things allocated in main
void	free_all_main(t_list *list, char ***env);

//get_next_line:
int		get_next_line(int fd, char **line, char **buffer);
char	*return_line(char *buffer);
char	*get_buffer(int fd, char *buffer);
char	*trim_buffer(char *buffer);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strlen_gnl(char *s);

//gnl_utils:
void	*ft_memcpy(void *dest, void *src, int n);
int		ft_strchr_gnl(char *s, int c);
char	*ft_substr(char *s, int start, int len);
void	*ft_calloc(int nmemb, int size);
void	ft_bzero(void *s, int n);

//execution:
int 	execute(t_list *list, char ***env);
void	forking(t_list *list, t_data *vars, char ***env);
void	case_with_pipes(t_list *list, t_data *vars, char **env);

//now_execute:
void	now_execute(t_data *vars, t_list *list, char ***env);
void	check_redirections(t_data *vars, t_list *list);

//pipes_managing:
void	free_pipes(t_data *vars);
void	create_pipes(t_data *vars);
void	redirect_stream(int input, int output);
void	closing_pipes(t_data *vars);

//check_files:
void	check_in_files(t_list *list, t_data *vars, char ***env);
void	check_out_files(t_list *list, t_data *vars, char ***env);
int		hd(t_list *list, int *fd);
int		here_doc(t_data *vars, t_list *list);
void	heredoc_err(t_data *vars, t_list *list);

//check_cmd_access:
void	checking_access(t_data *vars, t_list *list, char **env);
void	check_path(t_data *vars, t_list *list, char **envp);
//utils:
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp_ex(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen_ex(const char *str);
void	*ft_malloc(int size); //to be removed
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup_ex(char *s);
//size_t	ft_strlcat(char *dst, const char *src, size_t size);
int	ft_strlcat(char *dst, char *src, int size);
char	*ft_strcat(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

char	*ft_mystrncpy(char *dest, char *src, unsigned int n);

//utils_more:
int		ft_lstsize(t_list *lst);
int		ft_outfsize(t_outf *lst);
int		ft_infsize(t_inf *lst);
char	*ft_substr_split(char const *s, unsigned int start, size_t len);
char	**ft_split_ex(char const *s, char c);
char	*ft_strjoin_three(char const *s1, char ch, char const *s2);
char	*ft_strndup(char *s1, size_t n);

//built_in.c duplicating and freeind environment
int		builtin(char *cmd, t_list *list, char ***env);
char	**duplicate_env(char **env);
void	free_dup_env(char **env);

//cd:
int		if_cd_luck(char **env);
int		cd_home(char **env);
int		cd_with_argv(char **argv, char **env);
int		ft_cd(char **argv, char **env);

//env:
int		ft_env(char **env, char **argv);
char	*get_env_value(char **env, char *var, int len);
int		change_env_var(char **env, char *var, int len, char *new_value);

//echo:
int		ft_echo(char **argv);

//pwd:
int		ft_pwd(void);

//export:
void	add_env_var(char *arg, char **env);
void	add_str_arr(char *var, char ***env);
void	export_arg(char *arg, char ***env);
int		ft_export(char **argv, char ***env);

//unset:
int		ft_unset(char **argv, char **env);
int		unset_env_var(char **env, char *var, int len);

//exit:
int		ft_exit(t_list *list, char ***env);
void	check_argv_exit(t_list *list, int exit_val, char ***env);
int		is_sign(int c);
int		is_space(int c);
int		is_digit(int c);

char	*ft_substr(char *s, int start, int len);
int		is_special(char c);
void	ft_bzero(void *dest, int byte_sizes);
void	*ft_calloc(int num, int byte_sizes);
int		ft_strchrin(char *s, int c);
int		ft_strlen(char *s);
char	*count_special(char *s);
int		ft_count_words(char *s);
int		count_quotes(char *s);
char	**split_quotes(char *s, int *i, char **res);
char	**split_red(char *s, int *i, char **res);
char	**split_pipe(char *s, int *i, char **res);
char	**split_process(char *s, char **res);
char	**ft_split(char *s);
char	**get_tokens(char *user_input);


//strings
char	*ft_strdup(char *src);
char	*ft_strnstr(char *big, char *little, int len);
int		ft_strncmp(char *s1, char *s2, int n);\
int		ft_strlcpy(char *dst, char *src, int size);
int		is_alphanum(char c);


//init structs
t_list	*init_list(char **env_copy);
t_list	*ft_lstlast(t_list *lst);
void	add_last_list(t_list **head, t_list *last);
t_inf	*init_inf(char	*file, char flag);
t_inf	*ft_lstinf(t_inf *inf);
void	add_last_inf(t_inf **head, t_inf *inf);
t_outf	*init_outf(char	*file, char flag);
t_outf	*ft_lstoutf(t_outf *outf);
void	add_last_outf(t_outf **head, t_outf *outf);

//token expansions
t_list	*parse(char *user_input, char **tokens, char **env_copy);
void	parse_string(t_list **list, char *user_input, char **tokens);
char	*parse_no_q();
void	parse_exp(t_list **list, char **tokens, \
				char *user_input, char **env);
t_list	*parse_pipe(t_list **list, char **tokens, char **env);
void	parse_red(char **tokens, t_list **list);
void	add_next_outf(t_list **list, char *file, char *flag);
void	add_next_inf(t_list **list, char *file, char *flag);
int		is_special_str(char *str);







// //strings
// char	*ft_strrchr(char *s, int c);
// int		ft_strlen(char *s);
// int		ft_strncmp(char *s1, char *s2, int n);
// char	*ft_strstr(char *big, char *little);
// void	ft_putstr_fd(char *s, int fd);
// char	*ft_strjoin(char *s1, char *s2);
// int		ft_isspace(int c);
// char	*ft_strchr(char *s, int c);
// char	*ft_strcpy(char *dest, char *src);
// char	*ft_strdup(char *src);
// char	*ft_strndup(char *src, int len);



// //parsing
// void	prompt(void);

// char	**parse_user_input(char **user_input);
// char	*parse_argument(char **user_input);
// int		add_in_result(char *result, char *temp, int i, int index);
// int		add_in_argument(char **result, char *temp, int shift);
// char	*check_result(char *result, int index);


// //init
// // void	args_init(t_args *args);


// //utils
// void	*ft_malloc(int size);

// char	**ft_double_realloc(char **src, int size);
// void	*ft_realloc(char *src, int size);

#endif
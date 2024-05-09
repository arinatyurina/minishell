/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:23:44 by rtavabil          #+#    #+#             */
/*   Updated: 2024/05/09 20:24:17 by rtavabil         ###   ########.fr       */
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
# include <signal.h>
# include <sysexits.h>
# include <asm/termbits.h> 

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
	int		hd_id;
}		t_data;

typedef struct s_inf
{
	char			flag; // 'h' 'c' 
	char			*file;
	char			*hd_name;
	struct s_inf	*next;
}	t_inf;

typedef struct s_outf
{
	char			flag; // 'a' 'c'
	char			*file;
	struct s_outf	*next;
}		t_outf;

// list structure:
typedef struct s_list		t_list;
typedef struct s_list
{
	int				list_id;
	char			*cmd;
	char			**argv;
	char			**env;
	t_inf			*inf;
	t_outf			*outf;
	struct s_list	*next;
	int				hd_nbr;
	t_list			*head;
}		t_list;

typedef struct sigaction	t_sigaction;

//handle_heredoc:
void	hd_sigint_handler(int s);
void	hd_child(t_list *list, t_data *vars);
int		name_heredoc(t_list *list, t_data *vars, int i);
int		execute_hd(t_list *list, t_data *vars);
int		handle_heredoc(t_list *list, t_data *vars);
void	count_hd(t_list *list);

//handle_heredoc2
void	heredoc_err(t_data *vars, t_list *list);
void	ctrl_d_hd(t_list *list);
int		hd(t_list *list, int *fd);
void	here_doc(t_data *vars, t_list *list, char *name);
void	unlink_heredocs(t_list *list);

//signals:
void	signals_to_default(void);
void	sigint_handler(int sig);
void	init_signals(void);
int		waiting(t_data *vars);

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
int		execute(t_list *list, char ***env);
void	forking(t_list *list, t_data *vars, char ***env);
void	case_with_pipes(t_list *list, t_data *vars, char **env);

//now_execute:
void	now_execute(t_data *vars, t_list *list, char ***env);
void	if_path_null(t_data *vars, t_list *list, char ***env);
void	check_redirections(t_data *vars, t_list *list);

//pipes_managing:
void	free_pipes(t_data *vars);
void	create_pipes(t_data *vars);
void	redirect_stream(int input, int output);
void	redirect_back(t_data *vars);
void	closing_pipes(t_data *vars);

//check_files:
void	check_in_files(t_list *list, t_data *vars);
void	open_inf(t_list *list, t_data *vars, t_inf *copy);
void	check_out_files(t_list *list, t_data *vars);
void	open_outf(t_list *list, t_data *vars, t_outf *copy);
int		check_in_files_null(t_list *list, t_data *vars);
int		open_inf_null(t_list *list, t_data *vars);

//check_cmd_access:
void	checking_access(t_data *vars, t_list *list, char **env);
void	check_path(t_data *vars, t_list *list, char **envp);

//execution_utils
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp_ex(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen_ex(const char *str);
void	*ft_malloc(int size); //to be removed
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup_ex(char *s);
int		ft_strlcat(char *dst, char *src, int size);
char	*ft_strcat(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(char *s, int c);
int		ft_atoi(const char *nptr);
char	*ft_mystrncpy(char *dest, char *src, unsigned int n);
int		ft_lstsize(t_list *lst);
int		ft_outfsize(t_outf *lst);
int		ft_infsize(t_inf *lst);
char	*ft_substr_split(char *s, unsigned int start, size_t len);
char	**ft_split_ex(char *s, char c);
char	*ft_strjoin_three(char *s1, char ch, char *s2);
char	*ft_strndup(char *s1, size_t n);
char	*ft_itoa(int n);

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
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlcpy(char *dst, char *src, int size);
int		is_alphanum(char c);

//init structs
t_list	*init_list(char **env_copy, t_list *head);
t_list	*ft_lstlast(t_list *lst);
void	add_last_list(t_list **head, t_list *last);
t_inf	*init_inf(char	*file, char flag);
t_inf	*ft_lstinf(t_inf *inf);
void	add_last_inf(t_inf **head, t_inf *inf);
t_outf	*init_outf(char	*file, char flag);
t_outf	*ft_lstoutf(t_outf *outf);
void	add_last_outf(t_outf **head, t_outf *outf);

//token expansions
t_list	*parse(char **tokens, char **env_copy, int *exit_code);
void	parse_string(t_list **list, \
					char **tokens, int *exit_code);
char	*parse_no_q(char *str, char **env, int *exit_code);
void	parse_exp(t_list **list, char **tokens, \
				char *user_input, char **env);
t_list	*parse_pipe(t_list **list, char **tokens, char **env, int *exit_code);
void	parse_red(char **tokens, t_list **list, int *exit_code);
void	add_next_outf(t_list **list, char *file, char *flag);
void	add_next_inf(t_list **list, char *file, char *flag);
int		is_special_str(char *str);

//tokenizer
char	**split_quotes(char *s, int *i, char **res);
char	**split_red(char *s, int *i, char **res);
char	**split_pipe(char *s, int *i, char **res);
char	**split_exp(char *s, int *i, char **res);

//parsing
int		is_special_str(char *str);
void	add_next_inf(t_list **list, char *file, char *flag);
void	add_next_outf(t_list **list, char *file, char *flag);
char	*remove_quotes(char *str);
char	**ft_split_str(char *s); // for double quotes, to expand $ signs
int		get_num_tokens(char **tokens);
int		get_len_tokens(char	**tokens);
char	*merge_tokens(char **tokens);
void	free_double_array(char **array);
char	*parse_double(char *str, char **env, int *exit_code);
char	*parse_single(char *str);
char	**preparse(char *user_input, char **tokens, \
					char **env, int *exit_code);
void	add_argv(t_list **list, char *token);

//parsing with env
char	*return_env(char *token, char **env, int *exit_code);
char	**realloc_tokens(char **tokens, int index, char *value);
char	*get_env_parse(char *word, char **env, int *exit_code);
char	**replace_env(char **tokens, char **env, int *exit_code);

//input 
int		is_space(int c);
int		is_empty_str(char *str);
//free list
void	ft_clear_inf(t_inf **inf);
void	ft_clear_outf(t_outf **outf);
void	free_list(t_list **list);

#endif
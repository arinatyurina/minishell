# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 13:49:25 by rtavabil          #+#    #+#              #
#    Updated: 2024/05/09 19:48:33 by rtavabil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC := tokens.c token_utils.c token_utils2.c \
		token_utils3.c strings.c minishell.c \
		init_list.c init_inf.c init_outf.c\
		parse.c built_in.c check_cmd_access.c \
		echo_builtin.c execution.c export_builtin.c \
		now_execute.c pwd_builtin.c unset_builtin.c \
		execute_utils.c execute_utils2.c execute_utils3.c execute_utils4.c execute_utils5.c \
		cd_builtin.c check_files.c \
		env_builtin.c exit_builtin.c pipes_managing.c \
		handle_signals.c handle_heredoc.c handle_heredoc2.c \
		parse_red.c parse_utils.c token_utils4.c \
		parse_env.c parse_double.c parse_double_utils.c \
		parse_no_q.c preparse.c parse_pipe.c parse_add_argv.c \
		strings2.c check_files2.c
OBJ := $(SRC:%.c=%.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror

OBJ_PATH := obj/
OBJS := $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	@rm -rf $(OBJ_PATH) 

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean

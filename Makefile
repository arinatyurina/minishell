# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 13:49:25 by rtavabil          #+#    #+#              #
#    Updated: 2024/08/08 14:57:54 by rtavabil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
CC 			= cc -g3
CFLAGS 		= -Wall -Wextra -Werror

MAIN_SRCS 	= src/minishell.c \
src/parser/check_cmd_access.c src/parser/check_files.c src/parser/check_files2.c \
src/parser/init_inf.c src/parser/init_list.c src/parser/init_outf.c \
src/parser/parse_add_argv.c src/parser/parse_double_utils.c src/parser/parse_double.c \
src/parser/parse_env.c src/parser/parse_no_q.c src/parser/parse_pipe.c \
src/parser/parse_red.c src/parser/parse_utils.c src/parser/parse.c \
src/parser/preparse.c src/parser/strings.c src/parser/strings2.c \
src/parser/token_utils.c src/parser/token_utils2.c src/parser/token_utils3.c \
src/parser/token_utils4.c src/parser/tokens.c \
src/executor/builtin/built_in.c src/executor/builtin/cd_builtin.c src/executor/builtin/echo_builtin.c \
src/executor/builtin/env_builtin.c src/executor/builtin/exit_builtin.c src/executor/builtin/export_builtin.c \
src/executor/builtin/pwd_builtin.c src/executor/builtin/unset_builtin.c \
src/executor/execute_utils.c src/executor/execute_utils2.c src/executor/execute_utils3.c \
src/executor/execute_utils4.c src/executor/execute_utils5.c src/executor/execution.c \
src/executor/handle_heredoc.c src/executor/handle_heredoc2.c \
src/executor/handle_heredoc3.c src/executor/handle_signals.c src/executor/now_execute.c \
src/executor/pipes_managing.c


MAIN_OBJS = $(MAIN_SRCS:%.c=$(OBJ_F)%.o)


OBJ_F   = ./objs/
RM      = rm -rf


all: $(NAME)

$(NAME): $(MAIN_OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJS) -lreadline
	@printf "$(GREEN)==> Compiled ✅\n\n$(RESET)"


$(OBJ_F)%.o: %.c
	@printf "\033[0;33mGenerating objects... %-33.33s\r" $@
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ_F)*
	rm -d $(OBJ_F)
	@printf "$(GREEN)==>Cleaned ✅\n\n$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@printf "$(GREEN)==> Fully cleaned ✅\n\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft bonus

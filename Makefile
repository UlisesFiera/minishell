NAME		= 	minishell

CC			= 	cc

LIBFT		= 	./libft/libft.a

STD_FLAGS	= 	-Wall -Wextra -Werror -g
RL			=	-L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline
INC_FLAGS   = 	-I./libft -I./src

SRCS		= 	src/main/main.c \
				src/main/errors.c \
				src/main/welcome_message.c \
				src/main/signal.c \
				src/redirection/free_heredoc.c \
				src/main/init_data.c \
				src/main/init_data_handler.c \
				src/main/free_data.c \
				src/main/read_input.c \
				src/parsing/parsing.c \
				src/parsing/exec_counter.c \
				src/parsing/tokenizer.c \
				src/utils/check_closing_quotes.c \
				src/utils/ft_get_path.c \
				src/utils/ft_free_tab.c \
				src/utils/ft_get_env.c \
				src/utils/ft_strcmp.c \
				src/utils/ft_is_only_spaces.c \
				src/utils/file_finder.c \
				src/utils/ft_strinsert.c \
				src/utils/ft_is_digit_args.c \
				src/expansion/env_var_expansion.c \
				src/expansion/expand_token.c \
				src/expansion/field_split.c \
				src/expansion/field_split_utils.c \
				src/expansion/merge_quotes.c \
				src/redirection/heredoc.c \
				src/execution/execution_setup.c \
				src/execution/pipeline_builder.c \
				src/execution/pipeline_stream.c \
				src/execution/exec_builtin.c \
				src/execution/exec_env.c \
				src/execution/exec_commands.c \
				src/execution/exec_handlers.c \
				src/redirection/redirect_setup.c \
				src/redirection/heredoc_utils.c \
				src/redirection/redirect_exec.c \
				src/builts/echo.c \
				src/builts/cd.c \
				src/builts/pwd.c \
				src/builts/export.c \
				src/builts/export_checks.c \
				src/builts/export_utils.c \
				src/builts/export_utils2.c \
				src/builts/unset.c \
				src/builts/env.c \
				src/builts/exit.c \
				src/builts/export_var_exp.c \
				src/builts/export_sort.c \
				src/builts/export_validate.c \

OBJDIR		= 	build
OBJS		= 	$(patsubst src/%.c,${OBJDIR}/%.o,${SRCS})

REMOVE		= 	rm -f ${OBJS}

RED_DOT		= 	"\033[31m[●]\033[0m"
GREEN_DOT	= 	"\033[32m[●]\033[0m"
YELLOW_DOT	= 	"\033[33m[●]\033[0m"

all: ${LIBFT} ${NAME}

$(OBJDIR)/%.o: src/%.c
	@printf "\r\033[33m[●]\033[0m compiling minishell..."
	@mkdir -p $(dir $@)
	@${CC} ${STD_FLAGS} ${INC_FLAGS} -c $< -o $@ \
	|| { printf "\n\033[31m[●]\033[0m Error: minishell compilation failed!\n"; exit 1; }

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${STD_FLAGS} ${RL} ${LIBFT} -o ${NAME} \
	|| { printf "\n\033[31m[●]\033[0m Error: minishell compilation failed!\n"; exit 1; }
	@printf "\r\033[32m[●]\033[0m compiling minishell...\n"

${LIBFT}:
	@printf "\r\033[33m[●]\033[0m compiling and linking libft..."	
	@make --no-print-directory bonus -C ./libft > /dev/null 2>&1  \
	|| { printf "\n\033[31m[●]\033[0m Error: libft installation failed!\n"; exit 1; }
	@printf "\r\033[32m[●]\033[0m compiling and linking libft...\n"	

clean:
	@printf "\r\033[33m[●]\033[0m removing .o files..."		
	@${REMOVE}
	@make --no-print-directory clean -C ./libft clean > /dev/null 2>&1
	@printf "\r\033[32m[●]\033[0m removing .o files...\n"

fclean:	clean
	@printf "\r\033[33m[●]\033[0m removing executables..."
	@rm -f minishell
	@rm -rf build
	@make --no-print-directory fclean -C ./libft fclean > /dev/null 2>&1
	@printf "\r\033[32m[●]\033[0m removing executables...\n"
						
re:	fclean all

.PHONY:	all clean fclean re

.DEFAULT:
	@printf "\n\033[31m[●]\033[0m Error: no rule to make target '$@'\n"
	@false
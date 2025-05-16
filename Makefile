NAME 					= minishell

CC						= cc

LIBFT					= ./libft/libft.a

STD_FLAGS 				= -Wall -Wextra -Werror -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline

SRCS					= src/main.c \
						  src/read_input.c \
						  src/parsing.c \
						  src/init_data.c \
						  src/free_data.c \
						  src/exec_command.c \
						  src/fill_executables.c \
						  src/quotes_handle.c \
						  src/ft_get_path.c \
						  src/ft_free_tab.c \
						  src/ft_get_env.c \
						  src/ft_strcmp.c \
						  src/redirection/redirections.c \
						  src/redirection/append.c \
						  src/redirection/heredoc.c \
						  src/redirection/from_input.c \
						  src/redirection/to_output.c \
						  src/array_cleaner.c \
						  src/exec_pipe.c \
						  src/file_finder.c \


OBJS					= ${SRCS:.c=.o}

REMOVE					= rm -f ${OBJS}

all:					${LIBFT} ${NAME}

${NAME}:
						${CC} ${SRCS} ${LIBFT} ${STD_FLAGS} -o ${NAME}

${LIBFT}:				
						make bonus -C ./libft

clean:					
						${REMOVE}
						make clean -C ./libft

fclean:					clean
						make fclean -C ./libft
						rm -f minishell
						
re:						fclean all

.PHONY:					all clean fclean re
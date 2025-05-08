NAME 					= minishell

CC						= cc

LIBFT					= ./libft/libft.a

STD_FLAGS				= -Wall -Wextra -Werror -lreadline

SRCS					= src/main.c \
						  src/prompt.c \

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
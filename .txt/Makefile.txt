.PHONY : all clean fclean re

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -LLibft -lft -lreadline

INCLUDE = -I./Libft

NAME = minishell

SRC = ./minishell.c \
		./env.c \
		./paths.c \
		./parsing.c \
		./characters.c \
		./tokenisation.c \
		./formatting.c \
		./checking.c \
		./is_token_ok.c \
		./execution.c \
		./execution_utils.c \
		./here_doc.c \
		./redirections.c \
		./builtins.c \
		./builtins_env.c \
		./builtins_utils.c \
		./get.c \
		./lst_util.c \
		./sorting_utils.c \
		./utils.c \
		./double_tab.c \
		./init.c \
		./free.c \
		./close.c \
		./errors.c

OBJ = ${SRC:.c=.o}

%.o : %.c
	cc $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJ)
	cd Libft && make all
	cc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)
	rm -f heredoc.txt
	cd Libft && make clean

fclean : clean
	rm -f $(NAME)
	cd Libft && make fclean

re : fclean all
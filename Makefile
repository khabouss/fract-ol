NAME 	=	fractol
CC		= 	gcc
SRC		=	*.c
LIB		=	-I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
FLAGS	=	-Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	@clear
	@$(CC) -g $(SRC) $(LIB) $(FLAGS) -o $(NAME)

clean:
	@echo "Clean"

fclean:	clean
	@echo "Fclean"
	@(rm -rf $(NAME))
	@rm -rf *.dSYM

re:	fclean all

.PHONY : bonus clean fclean re
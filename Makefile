SRCS = main.c parse.c ray.c render.c vector.c 

OBJS = ${SRCS:.c=.o}

NAME = miniRT

LIBFT = Libft/libft.a

GNL = GNL/gnl.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror -g
RM = rm -f

INCLUDES = -I/usr/include -Imlx

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

all : $(NAME)

.c.o :
		${CC} ${C_FLAGS} -c $< -o ${<:.c=.o} $(INCLUDES)

$(NAME) : $(MLX) ${OBJS}
		  ${CC} ${C_FLAGS} ${OBJS} $(MLX_FLAGS) -lm -o ${NAME}


$(MLX) :
		@make -C ./mlx


clean :
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re

SRCS = main.c  check_the_map.c  minirt.c validation.c

SRCS_DIR = $(addprefix srcs/, $(SRCS))

OBJS = ${SRCS_DIR:.c=.o}

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

$(NAME) : ${LIBFT} ${GNL} $(MLX) ${OBJS}
		  ${CC} ${C_FLAGS} ${OBJS} ${LIBFT} $(MLX_FLAGS) ${GNL} -lm -o ${NAME}

$(LIBFT) :
		  @make -C ./Libft

$(MLX) :
		@make -C ./mlx

$(GNL) :
		@make -C ./GNL

clean :	
		@make clean -C ./Libft
		@make clean -C ./GNL
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME} ${LIBFT} ${GNL}

re : fclean all

.PHONY : all clean fclean re

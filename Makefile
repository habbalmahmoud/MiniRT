SRCS = main.c  check_the_map.c  minirt.c validation.c init.c ray.c light.c render.c vec.c plane.c cylinder.c cylinder_u.c

SRCS_DIR = $(addprefix srcs/, $(SRCS))

OBJS = ${SRCS_DIR:.c=.o}

NAME = miniRT

LIBFT = Libft/libft.a

GNL = GNL/gnl.a

MLX = minilibx-linux/libmlx.a

CC = cc
C_FLAGS = -Wall -Wextra -Werror -g
RM = rm -f

INCLUDES = -L ./lib/mlx -lmlx -lXext -lX11 -lm -lbsd


MLX_FLAGS = -lm -lXext -lX11

all : $(NAME)

.c.o :
		${CC} ${C_FLAGS} -c $< -o ${<:.c=.o} $(INCLUDES)

$(NAME) : ${LIBFT} ${GNL} $(MLX) ${OBJS}
		  ${CC} ${C_FLAGS} ${OBJS} ${LIBFT} ${MLX} $(MLX_FLAGS) ${GNL} -lm -o ${NAME}

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

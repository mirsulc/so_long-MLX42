NAME	=	so_long
CC	=	cc
FLAGS	=	-Wall -Werror -Wextra

SRC	=	src/main.c \
		src/count_characters.c \
		src/flood_fill.c \
		src/key_hook.c \
		src/map_check.c \
		src/render_map.c \
		src/cleaning.c

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
MLX_PATH	= MLX42/
MLX_NAME	= build/libmlx42.a
MLX		= $(MLX_PATH)$(MLX_NAME)

H_FILE	= include/so_long.h
RM	= rm -f

OBJ =		$(SRC:.c=.o)

MLX_FLAGS = -Iinclude -ldl -g -lglfw -pthread -lm


all: $(LIBFT) $(NAME) 

$(LIBFT):
	@make -C $(LIBFT_PATH)
	


$(NAME): $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX)  $(MLX_FLAGS)
	
clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: clean all

.PHONY: all clean fclean re 


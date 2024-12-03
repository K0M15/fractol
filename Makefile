.PHONY=all fractol fclean clean re mlx
NAME=fractol
CC=cc
FLAGS=-Wall -Wextra -Werror -g
FLAGS_APP= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX=lib/MLX42/build/libmlx42.a
FILES=src/main.c
FILES+=src/fractol.c
FILES+=src/help.c
F_INC=-Iinclude

all: mlx $(NAME)

mlx:
	cd lib/MLX42/ && cmake -B build && cmake --build build -j4

$(NAME): $(FILES:.c=.o)
	$(CC) $(FLAGS) $(FLAGS_APP) $(MLX) $(FILES:.c=.o) -o $(NAME) $(F_INC)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^ $(F_INC)

fclean: clean
	# cd lib/MLX42/build && make fclean
	rm -f $(NAME)
	# rm -f lib/MLX42/build/CMakeCache.txt

clean:
	cd lib/MLX42/build && make clean
	rm -f $(FILES:.c=.o)

re: fclean all
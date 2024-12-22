.PHONY=all fractol fclean clean re mlx
NAME=fractol
CC=cc
FLAGS=-Wall -Wextra -Werror
FLAGS_APP= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX=MLX42/build/libmlx42.a
FILES=src/main.c
FILES+=src/fractol.c
FILES+=src/help.c
FILES+=src/colormaps.c
FILES+=src/colormap_generator.c
FILES+=src/state.c
FILES+=src/controls.c
F_INC=-Iinclude

all: MLX42 $(NAME)

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

debug: FLAGS+=-g
debug: re

o: FLAGS+= -ffast-math -O3
o: re

$(NAME): $(FILES:.c=.o)
	$(CC) $(FLAGS) $(FLAGS_APP) $(MLX) $(FILES:.c=.o) -o $(NAME) $(F_INC)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^ $(F_INC)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(FILES:.c=.o)

re: fclean all

.PHONY=all fractol fclean clean re MLX42 FT_PRINTF
NAME=fractol
CC=cc
FLAGS=-Wall -Wextra -Werror
FLAGS_APP= -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLX=MLX42/build/libmlx42.a
PRINTF=ft_printf/libftprintf.a
FILES=src/main.c
FILES+=src/fractol.c
FILES+=src/help.c
FILES+=src/colormaps.c
FILES+=src/generators.c
FILES+=src/state.c
FILES+=src/input_controls.c
FILES+=src/ft_strncmp.c
FILES+=src/draw_loop.c
FILES+=src/render.c
FILES+=src/window_controls.c
F_INC=-Iinclude


all: FLAGS+=-ffast-math
all: FLAGS+=-O3
all: makeprintf MLX42 $(NAME)

makeprintf:
	cd ft_printf && make

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

debug: FLAGS+=-g
debug: re

$(NAME): $(FILES:.c=.o)
	$(CC) $(PRINTF) $(FLAGS) $(FLAGS_APP) $(MLX) $(FILES:.c=.o) -o $(NAME) $(F_INC)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^ $(F_INC)

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(FILES:.c=.o)

re: fclean all

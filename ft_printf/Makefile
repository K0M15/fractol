.PHONY: all clean fclean re norm

NAME=libftprintf.a
FILES=	ft_printf.o\
		ft_write_char.o \
		ft_write_hex.o \
		ft_write_number.o \
		ft_write_ptr.o \
		ft_write_string.o

SOURCE=$(FILES:.o=.c)

CFLAGS=-Wall -Wextra -Werror -g
CC=cc

all: $(NAME)

$(NAME): $(FILES) 
	ar -crs $(NAME) $(FILES)

clean:
	rm -f $(FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I.

norm:
	norminette $(SOURCE)

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:49:47 by afelger           #+#    #+#             */
/*   Updated: 2025/01/04 18:10:36 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libc.h>
# include <math.h>
# include "MLX42/MLX42.h"

# define WINDOW_TITLE "Fract'ol by Alain"
# define WIDTH		1920
# define HEIGHT		1080
# define START_ITERATION	12

typedef double t_ldb;

enum e_mode
{
	JULIA = 1,
	MANDELBROT = 2,
	TEST = 3,
	MODEMAX,
	ERROR
};

typedef struct s_vec4
{
	t_ldb	x;
	t_ldb	y;
	t_ldb	z;
	t_ldb	w;
}	t_vec4;

typedef struct s_vec2
{
	t_ldb	x;
	t_ldb	y;
}	t_vec2;

typedef struct s_screen
{
	int	width;
	int	height;
}	t_screen;

typedef unsigned int(* t_colormap)(unsigned char, int);
typedef struct s_fractal
{
	int (* fract)(t_vec2, t_ldb, t_ldb, int);
	t_vec2 init_vals;
}	t_fractal;

typedef struct s_appstate
{
	double			zoom;
	t_vec2			center;
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_colormap		*maps;
	int				selected_map;
	enum e_mode		mode;
	int				iteration;
	t_vec2			fractParam;
	unsigned int	depth;
	int				fc_en;
	unsigned int	fc;
	t_screen		screen;
}	t_appstate;

struct s_i32vec2 {
	int32_t x;
	int32_t y;
};

typedef struct s_renderpara
{
	int	startx;	// startpoint of x
	int	add;	// amount added to x/y
	int	fill;	// filled pixels
}	t_renderparam;

typedef struct s_renderstate
{
	int			x;
	int			y;
	int			i;
	int			j;
	int			col;
	t_screen	screen;
	t_vec2		buffer;
}	t_renderstate;

int julia_iter(t_vec2 pos, t_ldb jreal, t_ldb jimg, int max_iterations);
int mandelbrot_iter(t_vec2 pos, t_ldb real, t_ldb img, int max_iterations);
int test_iter(t_vec2 pos, t_ldb real, t_ldb img, int max_iterations);

t_vec2	*map_pixel_screen(t_vec2 *result, int x, int y, t_vec4 map, t_screen screen);
t_vec4	*calc_map_area(t_vec4 *result, t_vec2 center, double zoom);

# define COLORMAP_COUNT 5
unsigned int	colormap_crazy(unsigned char value, int depth);
unsigned int	colormap_red(unsigned char value, int depth);
unsigned int	colormap_green(unsigned char value, int depth);
unsigned int	colormap_blue(unsigned char value, int depth);
unsigned int	colormap_change(unsigned char value, int depth);
t_colormap		*get_maps(void);
# define MAPS state->maps[state->selected_map % COLORMAP_COUNT]

int				state_construct();
void			state_destruct();

void handle_zoom(double xdelta, double ydelta, t_appstate* state);
void handle_movement(t_appstate *state);
void handle_colorselect(t_appstate *state);
void handle_params_mod(t_appstate *state);
void handle_iterations(t_appstate *state);

void handle_resize(int32_t width, int32_t height,t_appstate *state);

void setup_interrupts(t_appstate *state);

void	display_help(void);
void	draw_fract(t_appstate *state);
void	render(t_appstate *state, t_vec4 map, t_renderparam para, int (* fract)(t_vec2, t_ldb, t_ldb, int));
t_appstate	*getstate(void);

int	ft_strncmp(const char *s1, const char *s2, unsigned long n);

#endif /* FRACTOL_H */
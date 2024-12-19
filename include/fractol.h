/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:49:47 by afelger           #+#    #+#             */
/*   Updated: 2024/12/19 15:53:47 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libc.h>
# include <math.h>
# include "MLX42/MLX42.h"

# define WIDTH		1920
# define HEIGHT		1080
# define PIXELS		WIDTH * HEIGHT
# define FRACT_DEPTH	255*3
# define START_ITERATION	5

# define ERR_MLX_INIT	0x1000
# define ERR_MLX_WIN	0x1001

typedef long double t_ldb;

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
	int	heigth;
}	t_screen;

typedef struct s_colormap
{
	int32_t *colors;
	uint32_t length;
}	t_colormap;

typedef struct s_appstate
{
	double		zoom;
	t_vec2		center;
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_colormap	*cmap;
	int			iteration;
}	t_appstate;

typedef struct s_renderpara
{
	int		startx;	// startpoint of x
	int		add;	// amount added to x
	int		fill;	// filled pixels
}	t_renderparam;

typedef int(*t_iter_func)(t_vec2 pos, t_ldb jreal, t_ldb jimg, int max_iterations);

int julia_iter(t_vec2 pos, t_ldb jreal, t_ldb jimg, int max_iterations);
int mandelbrot_iter(t_vec2 pos, t_ldb real, t_ldb img, int max_iterations);

t_vec2 *map_pixel_screen(t_vec2 *result, int x, int y, t_vec4 map, t_screen screen);
t_vec4	*calc_map_area(t_vec4 *result, t_vec2 center, double zoom);

#endif /* FRACTOL_H */
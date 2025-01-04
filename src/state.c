/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:32:39 by afelger           #+#    #+#             */
/*   Updated: 2025/01/04 20:08:05 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static enum e_mode	parsemode(int argc, char **args)
{
	int			c;
	enum e_mode	mode;

	c = -1;
	mode = ERROR;
	while (++c < argc)
	{
		if (ft_strncmp(args[c], "julia", 5) == 0)
			mode = JULIA;
		else if (ft_strncmp(args[c], "mandelbrot", 10) == 0)
			mode = MANDELBROT;
		else if (ft_strncmp(args[c], "test", 10) == 0)
			mode = TEST;
		else if (ft_strncmp(args[c], "-h", 2) == 0)
		{
			mode = ERROR;
			break ;
		}
	}
	if (mode == ERROR)
		display_help();
	return (mode);
}

static void	init_mode_vals(t_appstate *state)
{
	if (state->mode >= MODEMAX)
		exit(EXIT_FAILURE);
	if (state->mode == JULIA)
	{
		state->center.x = .0;
		state->center.y = .0;
		state->fractParam.x = -0.7;
		state->fractParam.y = 0.27015;
	}
	else if (state->mode == MANDELBROT)
	{
		state->center.x = -.8;
		state->center.y = 0.0;
		state->fractParam.x = 0;
		state->fractParam.y = 0;
		state->zoom = .5;
	}
	else if (state->mode == TEST)
	{
		state->center.x = .0;
		state->center.y = .0;
		state->fractParam.x = 0;
		state->fractParam.y = 0;
	}
}

int	state_construct(t_appstate *s, int argc, char **argv)
{
	memset(s, 0, sizeof(t_appstate));
	s->zoom = 1.0;
	s->mode = parsemode(argc, argv);
	init_mode_vals(s);
	s->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	s->iteration = START_ITERATION;
	s->maps = get_maps();
	s->depth = 100;
	s->screen.height = HEIGHT;
	s->screen.width = WIDTH;
	if (!s->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	s->image = mlx_new_image(s->mlx, s->screen.width * 2, s->screen.height * 2);
	mlx_set_window_limit(s->mlx, -1, -1, s->image->width, s->image->height);
	if (mlx_image_to_window(s->mlx, s->image, 0, 0) == -1)
	{
		mlx_close_window(s->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	setup_interrupts(t_appstate *state)
{
	mlx_scroll_hook(state->mlx, (mlx_scrollfunc) handle_zoom, state);
	mlx_resize_hook(state->mlx, (mlx_resizefunc) handle_resize, state);
}

void	state_destruct(t_appstate *state)
{
	free(state->maps);
	mlx_terminate(state->mlx);
}

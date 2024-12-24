/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:32:39 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 14:39:56 by afelger          ###   ########.fr       */
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

int	state_construct(t_appstate *state, int argc, char **argv)
{
	memset(state, 0, sizeof(t_appstate));
	state->zoom = 1.0;
	state->mode = parsemode(argc, argv);
	init_mode_vals(state);
	state->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	state->iteration = START_ITERATION;
	state->maps = get_maps();
	state->depth = 100;
	if (!state->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	state->image = mlx_new_image(state->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(state->mlx, state->image, 0, 0) == -1)
	{
		mlx_close_window(state->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	setup_interrupts(t_appstate *state)
{
	mlx_scroll_hook(state->mlx, (mlx_scrollfunc) handle_zoom, state);
}

void	state_destruct(t_appstate *state)
{
	free(state->maps);
	mlx_terminate(state->mlx);
}

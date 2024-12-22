/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:32:39 by afelger           #+#    #+#             */
/*   Updated: 2024/12/22 14:29:31 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	state_construct(t_appstate *state)
{
	memset(state, 0, sizeof(t_appstate));
	state->zoom = 1.0;
	state->center.x = .0;
	state->center.y = .0;
	state->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_TITLE, true);
	state->iteration = START_ITERATION;
	state->fractParam.x = -0.7;
	state->fractParam.y = 0.27015;
	state->maps = get_maps();
	state->fractals = get_fracts();
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

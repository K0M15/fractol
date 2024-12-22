/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:47:49 by afelger           #+#    #+#             */
/*   Updated: 2024/12/22 13:45:17 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

struct ivec2 {
	int32_t x;
	int32_t y;
};

void handle_zoom(double xdelta, double ydelta, t_appstate* state)
{
	struct ivec2	cursor;
	t_vec2			before, after;
	t_vec4			map;
	t_screen		screen;

	(void) xdelta;
	screen.width = WIDTH;
	screen.heigth = HEIGHT;
	calc_map_area(&map, state->center, state->zoom);
	mlx_get_mouse_pos(state->mlx, &cursor.x, &cursor.y);
	map_pixel_screen(&before, cursor.x, cursor.y, map, screen);
	if (ydelta < 0)
		state->zoom *= 1.1;
	else if (ydelta > 0)
		state->zoom *= 0.9;
	calc_map_area(&map, state->center, state->zoom);
	map_pixel_screen(&after, cursor.x, cursor.y, map, screen);
	state->center.x += before.x - after.x;
	state->center.y += before.y - after.y;
	state->iteration = START_ITERATION;
}

void handle_movement(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_UP))
	{
		state->center.y -= 0.1/ state->zoom;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_DOWN))
	{
		state->center.y += 0.1/ state->zoom;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_LEFT))
	{
		state->center.x -= 0.1/ state->zoom;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_RIGHT))
	{
		state->center.x += 0.1/ state->zoom;
		state->iteration = START_ITERATION;
	}
}

void handle_colorselect(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_C))
	{
		state->selected_map += 1;
		state->iteration = START_ITERATION;
	}
}

void handle_params_mod(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_K))
	{
		state->fractParam.x -= 0.0001;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_I))
	{
		state->fractParam.x += 0.0001;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_J))
	{
		state->fractParam.y -= 0.0001;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_L))
	{
		state->fractParam.y += 0.0001;
		state->iteration = START_ITERATION;
	}
}

void handle_iterations(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_2))
	{
		state->depth += 10;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_1))
	{
		state->depth -= 10;
		state->iteration = START_ITERATION;
	}
}
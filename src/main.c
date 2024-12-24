/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:23:56 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 14:30:51 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"

void ft_hook(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx);
	handle_movement(state);
	handle_colorselect(state);
	handle_params_mod(state);
	handle_iterations(state);	
}

void ft_loop(t_appstate *state)
{
	ft_hook(state);
	draw_fract(state);
	state->fc++;
}

void scrollfunc(double xdelta, double ydelta, t_appstate* state)
{
	(void) xdelta;
	state->zoom *= ydelta + 1;
	state->iteration = START_ITERATION;
}

t_appstate	*getstate(void)
{
	static t_appstate	state;
	return (&state);
}

int32_t main(int argc, char **argv)
{
	t_appstate *state;
	int buff;

	state = getstate();
	buff = state_construct(state, argc, argv);
	if(buff != 0)
		return buff;
	setup_interrupts(state);
	mlx_loop_hook(state->mlx, (void (*)(void*))ft_loop, state);
	mlx_loop(state->mlx);
	state_destruct(state);
	return (EXIT_SUCCESS);
}

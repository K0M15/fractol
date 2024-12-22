// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

# include "../include/fractol.h"


void	render_julia_iter(t_appstate *state, t_vec4 map, t_renderparam para)
{
	int	x, y, i, j;
	int col;
	t_screen screen = {WIDTH, HEIGHT};
	t_vec2 buffer;

	x = para.startx;
	y = 0;
	while(y < HEIGHT)
	{
		x = para.startx;
		while (x < WIDTH)
		{
			map_pixel_screen(&buffer, x, y, map, screen);
			col = FRACT(buffer, state->fractParam.x, state->fractParam.y, state->depth);
			j = 0;
			while (j < para.add && y + j < HEIGHT)
			{
				i = 0;
				while(i < para.add && x + i < WIDTH)
				{
					mlx_put_pixel(state->image, x + i, y + j, MAPS(col, state->depth));
					i++;
				}
				j++;
			}
			x += para.add;
		}
		y += para.add;
	}
}

void	draw_fract(t_appstate *state)
{
	t_vec4 map;
	t_renderparam param;
	
	calc_map_area(&map, state->center, state->zoom);
	param.add = 4;
	if(state->iteration == 5)
	{
		param.fill=4;
		param.startx = 0;
		param.add= 8;
	}
	else if (state->iteration == 4)
	{
		param.fill= 3;
		param.startx = 4;
		param.add= 8;
	}
	else if (state->iteration == 3)
	{
		param.fill = 2;
		param.startx = 2;
	}
	else if (state->iteration == 2)
	{
		param.fill = 1;
		param.startx = 1;
		param.add  = 2;
	}
	else if (state->iteration == 1)
	{
		param.fill = 1;
		param.startx = 3;
		param.add  = 2;
	}
	if(state->iteration > 0){
		render_julia_iter(state, map, param);
		state -> iteration--;
	}
}

void ft_hook(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx);
	handle_movement(state);
	handle_colorselect(state);
	handle_params_mod(state);
	handle_iterations(state);	
	handle_fract_select(state);
}

void ft_loop(t_appstate *state)
{
	ft_hook(state);
	draw_fract(state);
}

void scrollfunc(double xdelta, double ydelta, t_appstate* state)
{
	(void) xdelta;
	state->zoom *= ydelta + 1;
	state->iteration = START_ITERATION;
}

int32_t main(void)
{
	t_appstate state;
	int buff;
	
	buff = state_construct(&state);
	if(buff != 0)
		return buff;
	setup_interrupts(&state);
	mlx_loop_hook(state.mlx, (void (*)(void*))ft_loop, &state);
	mlx_loop(state.mlx);
	state_destruct(&state);
	return (EXIT_SUCCESS);
}

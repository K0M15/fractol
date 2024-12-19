// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

# include "../include/fractol.h"

int32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int colormap2(unsigned char value) {
    unsigned char r, g, b;

	r = value;
	g = (value*value)%255;
	b = (int)(value*0.5);

    return (r << 24) | (g << 16) | (b << 8) | 0xff;
}

unsigned int colormap(unsigned char value) {
    unsigned char r, g, b;

	r = (char)((float)value/(float)FRACT_DEPTH * 255);
	g = 0;
	b = 0;

    return (r << 24) | (g << 16) | (b << 8) | 0xff;
}

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
			col = julia_iter(buffer, state->fractParam.x, state->fractParam.y, state->depth);
			j = 0;
			while (j < para.add && y + j < HEIGHT)
			{
				i = 0;
				while(i < para.add && x + i < WIDTH)
				{
					mlx_put_pixel(state->image, x + i, y + j, colormap(col%255));
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
	printf("drawn %i\n", state->iteration);
}

void ft_hook(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx);
	if (mlx_is_key_down(state->mlx, MLX_KEY_W))
	{
		state->zoom *= 1.50;
		state->iteration = START_ITERATION;
	}
	if (mlx_is_key_down(state->mlx, MLX_KEY_S))
	{
		state->zoom /= 1.50;
		state->iteration = START_ITERATION;
	}
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
	if (mlx_is_key_down(state->mlx, MLX_KEY_H))
	{
		state->center.x = 0;
		state->zoom = 1;
		state->center.y = 0;
		state->iteration = START_ITERATION;
	}
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

void ft_loop(t_appstate *state)
{
	// if (state->iteration != 0)
	// {
		ft_hook(state);
		draw_fract(state);
	// }
}
int32_t main(void)
{
	t_appstate state;

	memset(&state, 0, sizeof(t_appstate));
	state.zoom = 1.0;
	state.center.x = .0;
	state.center.y = .0;
	state.mlx = mlx_init(WIDTH, HEIGHT, "Fract'ol by Alain", true);
	state.iteration = START_ITERATION;
	state.fractParam.x =  -0.7;
	state.fractParam.y =  0.27015;
	state.depth = 30;
	if (!state.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	state.image = mlx_new_image(state.mlx, WIDTH, HEIGHT);
	if (!(state.image))
	{
		mlx_close_window(state.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(state.mlx, state.image, 0, 0) == -1)
	{
		mlx_close_window(state.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// mlx_loop_hook(state.mlx, (void (*)(void*))draw_fract, &state);
	// mlx_loop_hook(state.mlx, (void (*)(void*))ft_hook, &state);
	mlx_loop_hook(state.mlx, (void (*)(void*))ft_loop, &state);
	mlx_loop(state.mlx);
	mlx_terminate(state.mlx);
	return (EXIT_SUCCESS);
}

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

# include "../include/fractol.h"

#define WIDTH 1920
#define HEIGHT 1024


int32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void draw_fract(t_appstate *state)
{
	int x;
	t_vec4 map;
	t_screen screen = {WIDTH, HEIGHT};
	int col;
	t_vec2 buffer;
	
	calc_map_area(&map, state->center, state->zoom);
	x = 0;
	while (x < WIDTH * HEIGHT)
	{
		map_pixel_screen(&buffer, x%WIDTH, x/WIDTH, map, screen);
		col = julia_iter(buffer, -0.7, 0.27015, 1000);
		mlx_put_pixel(state->image, x%WIDTH, x/WIDTH, ft_color(((col<<3)%255)*255, (col%255)*255, 122, 128));
		x++;
	}
}

void ft_hook(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx);
	if (mlx_is_key_down(state->mlx, MLX_KEY_UP))
		state->zoom *= 1.50;
	if (mlx_is_key_down(state->mlx, MLX_KEY_DOWN))
		state->zoom /= 1.50;
}
int32_t main(void)
{
	t_appstate state;

	memset(&state, 0, sizeof(t_appstate));
	state.zoom = 1;
	state.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
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
	mlx_loop_hook(state.mlx, (void (*)(void*))draw_fract, &state);
	mlx_loop_hook(state.mlx, (void (*)(void*))ft_hook, &state);
	mlx_loop(state.mlx);
	mlx_terminate(state.mlx);
	return (EXIT_SUCCESS);
}

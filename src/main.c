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

unsigned int colormap(unsigned char value) {
    unsigned char r, g, b;

    if (value < 43) {
        r = 255;
        g = (unsigned char)(value * 6);
        b = 0;
    } else if (value < 85) {
        r = (unsigned char)(255 - ((value - 43) * 6));
        g = 255;
        b = 0;
    } else if (value < 128) {
        r = 0;
        g = 255;
        b = (unsigned char)((value - 85) * 6);
    } else if (value < 170) {
        r = 0;
        g = (unsigned char)(255 - ((value - 128) * 6));
        b = 255;
    } else if (value < 213) {
        r = (unsigned char)((value - 170) * 6);
        g = 0;
        b = 255;
    } else {
        r = 255;
        g = 0;
        b = (unsigned char)(255 - ((value - 213) * 6));
    }

    return (r << 24) | (g << 16) | (b << 8) | 0xff;
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
		col = julia_iter(buffer, -0.7, 0.27015, 30);
		mlx_put_pixel(state->image, x%WIDTH, x/WIDTH, colormap(col%255));
		x++;
	}
}

void ft_hook(t_appstate *state)
{
	if (mlx_is_key_down(state->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(state->mlx);
	if (mlx_is_key_down(state->mlx, MLX_KEY_W))
		state->zoom *= 1.50;
	if (mlx_is_key_down(state->mlx, MLX_KEY_S))
		state->zoom /= 1.50;
	if (mlx_is_key_down(state->mlx, MLX_KEY_UP))
		state->center.y += 0.1/ state->zoom;
	if (mlx_is_key_down(state->mlx, MLX_KEY_DOWN))
		state->center.y -= 0.1/ state->zoom;
	if (mlx_is_key_down(state->mlx, MLX_KEY_LEFT))
		state->center.x -= 0.1/ state->zoom;
	if (mlx_is_key_down(state->mlx, MLX_KEY_RIGHT))
		state->center.x += 0.1/ state->zoom;
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

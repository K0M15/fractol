/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:05:08 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 14:42:14 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_square(t_renderstate *renders,
	t_renderparam *para, t_appstate *state)
{
	renders->j = 0;
	while (renders->j < para->fill && renders->y + renders->j < HEIGHT)
	{
		renders->i = 0;
		while (renders->i < para->fill && renders->x + renders->i < WIDTH)
		{
			mlx_put_pixel(state->image, renders->x + renders->i,
				renders->y + renders->j, MAPS(renders->col, state->depth));
			renders->i++;
		}
		renders->j++;
	}
}

void	render(t_appstate *state, t_vec4 map,
	t_renderparam para, int (*fract)(t_vec2, t_ldb, t_ldb, int))
{
	t_renderstate	renders;

	renders.y = 0;
	renders.screen.heigth = HEIGHT;
	renders.screen.width = HEIGHT;
	while (renders.y < HEIGHT)
	{
		renders.x = para.startx;
		while (renders.x < WIDTH)
		{
			map_pixel_screen(&renders.buffer, renders.x,
				renders.y, map, renders.screen);
			renders.col = fract(renders.buffer, state->fractParam.x,
					state->fractParam.y, state->depth);
			render_square(&renders, &para, state);
			renders.x += para.add;
		}
		renders.y += para.fill;
	}
}

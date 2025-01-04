/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:05:08 by afelger           #+#    #+#             */
/*   Updated: 2025/01/04 18:12:48 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_square(t_renderstate *renders,
	t_renderparam *para, t_appstate *state)
{
	renders->j = 0;
	while (renders->j < para->fill && renders->y + renders->j < state->screen.height)
	{
		renders->i = 0;
		while (renders->i < para->fill && renders->x + renders->i < state->screen.width)
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
	renders.screen.height = state->screen.height;
	renders.screen.width = state->screen.width;
	while (renders.y < state->screen.height)
	{
		renders.x = para.startx;
		while (renders.x < state->screen.width)
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

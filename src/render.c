/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:05:08 by afelger           #+#    #+#             */
/*   Updated: 2025/01/13 13:52:38 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_square(t_renderstate *r,
	t_renderparam *para, t_appstate *state)
{
	r->j = 0;
	while (r->j < para->fill && r->y + r->j < state->screen.height)
	{
		r->i = 0;
		while (r->i < para->fill && r->x + r->i < state->screen.width)
		{
			mlx_put_pixel(state->image, r->x + r->i,
				r->y + r->j, state->maps[
				state->selected_map % COLORMAP_COUNT](r->col, state->depth));
			r->i++;
		}
		r->j++;
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
			map_pixel_screen(&renders.buffer, (struct s_i32vec2){renders.x,
				renders.y}, map, renders.screen);
			renders.col = fract(renders.buffer, state->fractparam.x,
					state->fractparam.y, state->depth);
			render_square(&renders, &para, state);
			renders.x += para.add;
		}
		renders.y += para.fill;
	}
}

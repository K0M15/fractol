/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:54:09 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 14:02:32 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void assign_param(t_renderparam *p, int add, int fill, int startx)
{
	p->add = add;
	p->fill = fill;
	p->startx = startx;
}

static void	decide_param(t_appstate *state, t_renderparam *param)
{
	if(state->iteration == 12)
		assign_param(param, 8, 8, 0);
	else if(state->iteration == 11)
		assign_param(param, 8, 5, 4);
	else if(state->iteration == 10)
		assign_param(param, 8, 3, 4);
	else if(state->iteration == 9)
		assign_param(param, 8, 3, 6);
	else if(state->iteration == 8)
		assign_param(param, 8, 1, 7);
	else if(state->iteration == 7)
		assign_param(param, 8, 1, 6);
	else if(state->iteration == 6)
		assign_param(param, 8, 1, 5);
	else if(state->iteration == 5)
		assign_param(param, 8, 1, 4);
	else if(state->iteration == 4)
		assign_param(param, 8, 1, 3);
	else if(state->iteration == 3)
		assign_param(param, 8, 1, 2);
	else if(state->iteration == 2)
		assign_param(param, 8, 1, 1);
	else if(state->iteration == 1)
		assign_param(param, 8, 1, 0);
}

void	draw_fract(t_appstate *state)
{
	t_vec4 map;
	t_renderparam param;
	
	calc_map_area(&map, state->center, state->zoom);
	decide_param(state, &param);
	if(state->iteration > 0){
		if (state->mode == JULIA)
			render(state, map, param, julia_iter);
		else if (state->mode == MANDELBROT)
			render(state, map, param, mandelbrot_iter);
		else if (state->mode == TEST)
			render(state, map, param, test_iter);
		state -> iteration--;
	}
}

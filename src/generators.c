/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:51:28 by afelger           #+#    #+#             */
/*   Updated: 2024/12/22 14:56:16 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_colormap	*get_maps(void)
{
	t_colormap	*result;

	result = malloc(COLORMAP_COUNT * sizeof(t_colormap));
	result[0] = colormap_crazy;
	result[1] = colormap_red;
	result[2] = colormap_green;
	result[3] = colormap_blue;
	return (result);
}
//THIS NEEDS A REDO!
t_fractal	*get_fracts(void)
{
	t_fractal *result;

	result = malloc(FRACTAL_COUNT * sizeof(t_fractal));
	result[0].fract = julia_iter;
	result[0].init_vals.x = -0.7;
	result[0].init_vals.y = 0.27015;
	result[1].fract = mandelbrot_iter;
	result[1].init_vals.x = 0;
	result[1].init_vals.y = 0;
	return (result);
}

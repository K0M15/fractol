/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:49:45 by afelger           #+#    #+#             */
/*   Updated: 2024/12/22 12:46:06 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int julia_iter(t_vec2 pos, t_ldb jreal, t_ldb jimg, int max_iterations)
{
	int		iter;
	t_ldb	temp;

	iter = 0;
	while (pos.x * pos.x + pos.y * pos.y <= 4 && iter < max_iterations)
	{
		temp = pos.x * pos.x - pos.y * pos.y + jreal;
		pos.y = 2 * pos.x * pos.y + jimg;
		pos.x = temp;
		iter++;
	}
	if (iter == max_iterations)
		return (0);
	return (iter);
}

int mandelbrot_iter(t_vec2 pos, t_ldb real, t_ldb img, int max_iterations)
{
	int		iter;
	t_vec2	buffer;
	
	iter = 0;
	while (real * real + img * img < 4 && iter < max_iterations)
	{
		buffer.x = real * real - img * img + pos.x;
		buffer.y = 2 * real * img * img;
		real = buffer.x;
		img = buffer.y;
		iter++;
	}
	if (iter == max_iterations)
		return (0);
	return (iter);
}

t_vec2 *map_pixel_screen(t_vec2 *result, int x, int y, t_vec4 map, t_screen screen)
{

	result->x = (long double)x / screen.width * (map.z - map.x) + map.x;
	result->y = (long double)y / screen.heigth * (map.w - map.y) + map.y;
	return (result);
}

t_vec4	*calc_map_area(t_vec4 *result, t_vec2 center, double zoom){
	double edgelen;

	edgelen = 1.5/zoom;
	result->x = center.x - edgelen/2.0;
	result->y = center.y - edgelen/2.0;
	result->z = center.x + edgelen/2.0;
	result->w = center.y + edgelen/2.0;
	return (result);
}
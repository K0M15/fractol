/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormaps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:47:12 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 14:54:36 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	colormap_crazy(unsigned char value, int depth)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	(void) depth;
	r = value;
	g = (value * value) % 255;
	b = (int)(value * 0.5);
	return ((r << 24) | (g << 16) | (b << 8) | 0xff);
}

unsigned int	colormap_red(unsigned char value, int depth)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (char)((float)value / (float)depth * 255);
	g = 0;
	b = 0;
	return ((r << 24) | (g << 16) | (b << 8) | 0xff);
}

unsigned int	colormap_green(unsigned char value, int depth)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	g = (char)((float)value / (float)depth * 255);
	b = 0;
	r = 0;
	return ((r << 24) | (g << 16) | (b << 8) | 0xff);
}

unsigned int	colormap_blue(unsigned char value, int depth)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	b = (char)((float)value / (float)depth * 255);
	r = 0;
	g = 0;
	return ((r << 24) | (g << 16) | (b << 8) | 0xff);
}

unsigned int	colormap_change(unsigned char value, int depth)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	(void) depth;
	value += getstate()->fc;
	r = value;
	g = (value * value) % 255;
	b = (int)(value * 0.5);
	return ((r << 24) | (g << 16) | (b << 8) | 0xff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:54:27 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 12:58:14 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	display_help(void)
{
	ft_printf("usage: fractol  [-h] fractname\n");
	ft_printf("Supported fractname \"julia\" \"mandelbrot\" \"dragon\"\n");
	ft_printf("	-h					Display this message\n");
	ft_printf("\n");
	ft_printf("Controlls:\n");
	ft_printf("	Mouse + Wheel:		Zoom to location\n");
	ft_printf("	j+l / i+k:			change real/imagenary part of equation\n");
	ft_printf("	1/2:				increase/decrease amount of iterations of equation\n");
	ft_printf("	c:					change color scheme\n");
	ft_printf("	ESC:				quit\n");
}
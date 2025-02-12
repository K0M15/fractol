/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:51:28 by afelger           #+#    #+#             */
/*   Updated: 2024/12/24 14:48:01 by afelger          ###   ########.fr       */
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
	result[4] = colormap_change;
	return (result);
}

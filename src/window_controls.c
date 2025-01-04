/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:48:15 by afelger           #+#    #+#             */
/*   Updated: 2025/01/04 18:09:22 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_resize(int32_t width, int32_t height, t_appstate *state)
{
	state->screen.height = height;
	state->screen.width = width;
	state->iteration = START_ITERATION;
}
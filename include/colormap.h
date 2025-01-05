/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:36:18 by afelger           #+#    #+#             */
/*   Updated: 2025/01/05 16:39:09 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORMAP_H
# define COLORMAP_H
# include "MLX42.h"

# define COLORMAP_COUNT 5

typedef uint32_t	(*t_colormap)(unsigned char value, int depth);
unsigned int		colormap_crazy(unsigned char value, int depth);
unsigned int		colormap_red(unsigned char value, int depth);
unsigned int		colormap_green(unsigned char value, int depth);
unsigned int		colormap_blue(unsigned char value, int depth);
unsigned int		colormap_change(unsigned char value, int depth);
t_colormap			*get_maps(void);

#endif
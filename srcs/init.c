/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:55:05 by mhabbal           #+#    #+#             */
/*   Updated: 2025/04/16 09:55:06 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	close_window(int keycode)
{
	if (keycode == 65307)
	{
		exit(0);
	}
	return (0);
}

int	init(t_cor *scenee)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	if (!mlx.ptr)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "miniRT");
	mlx.img = mlx_new_image(mlx.ptr, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel,
			&mlx.line_length, &mlx.endian);
	render_scene(&mlx, scenee);
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img, 0, 0);
	mlx_key_hook(mlx.win_ptr, close_window, 0);
	mlx_loop(mlx.ptr);
	return (0);
}

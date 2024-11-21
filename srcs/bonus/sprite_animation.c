/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:21:55 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/21 12:52:13 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_torch_textures(t_cub3d *cub3d)
{
	int		i;
	char	*torch_name;

	i = 1;
	cub3d->torch_textures = ft_calloc(sizeof(mlx_texture_t *), N_TORCH_TXTRS);
	if (!cub3d->torch_textures)
		execution_error_handler(cub3d, 9);
	while (i - 1 < N_TORCH_TXTRS)
	{
		torch_name = ft_strjoin_free_s2("textures/torch", ft_itoa(i), ".png");
		if (torch_name == NULL)
			execution_error_handler(cub3d, 9);
		cub3d->torch_textures[i - 1] = mlx_load_png(torch_name);
		free(torch_name);
		if (cub3d->torch_textures[i - 1] == NULL)
			execution_error_handler(cub3d, 6);
		i++;
	}
}

void	load_torch_images_to_screen(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	cub3d->torch_images = ft_calloc(sizeof(mlx_image_t *), N_TORCH_TXTRS);
	if (!cub3d->torch_images)
		execution_error_handler(cub3d, 9);
	while (i < N_TORCH_TXTRS)
	{
		cub3d->torch_images[i] = mlx_texture_to_image(cub3d->mlx, \
													cub3d->torch_textures[i]);
		if (cub3d->torch_images[i] == NULL)
			execution_error_handler(cub3d, 7);
		if (mlx_image_to_window(cub3d->mlx, cub3d->torch_images[i], \
								WIDTH - 300, HEIGHT - 650) == -1)
			execution_error_handler(cub3d, 8);
		cub3d->torch_images[i]->instances->enabled = false;
		mlx_delete_texture(cub3d->torch_textures[i]);
		cub3d->torch_textures[i] = NULL;
		i++;
	}
	free(cub3d->torch_textures);
	cub3d->torch_textures = NULL;
	cub3d->torch_images[0]->instances->enabled = true;
}

static long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	update_torch(void *param)
{
	static int			i = 0;
	static long long	last_frame;
	t_cub3d				*cub3d;

	cub3d = (t_cub3d *)param;
	if (get_current_time() - last_frame < 100)
		return ;
	cub3d->torch_images[i]->instances->enabled = false;
	i++;
	if (i == N_TORCH_TXTRS)
		i = 0;
	cub3d->torch_images[i]->instances->enabled = true;
	last_frame = get_current_time();
}

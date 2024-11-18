/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:21:55 by saleunin          #+#    #+#             */
/*   Updated: 2024/11/18 15:42:51 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_torch_name(t_cub3d *cub3d, int i)
{
	char	*i_str;
	char	*str;
	char	*torch_name;

	i_str = ft_itoa(i);
	if (!i_str)
		close_program(cub3d, ENOMEM);
	str = ft_strjoin("textures/torch", i_str);
	free(i_str);
	if (!str)
		close_program(cub3d, ENOMEM);
	torch_name = ft_strjoin(str, ".png");
	free(str);
	if (!torch_name)
		close_program(cub3d, ENOMEM);
	return (torch_name);
}

static mlx_image_t	*mlx_open_torch_img(t_cub3d *cub3d, int i)
{
	char			*torch_name;
	mlx_texture_t	*torch;
	mlx_image_t		*img;

	torch_name = get_torch_name(cub3d, i);
	torch = mlx_load_png(torch_name);
	free(torch_name);
	if (torch == NULL)
		close_program(cub3d, 1);
	img = mlx_texture_to_image(cub3d->mlx, torch);
	mlx_delete_texture(torch);
	if (img == NULL)
		close_program(cub3d, 1);
	return (img);
}

void	load_torches(t_cub3d *cub3d)
{
	int		i;

	i = 1;
	cub3d->torch_images = malloc(sizeof(mlx_image_t *) * N_TORCH_TXTRS);
	if (!cub3d->torch_images)
		close_program(cub3d, 1);
	while (i - 1 < N_TORCH_TXTRS)
	{
		cub3d->torch_images[i - 1] = mlx_open_torch_img(cub3d, i);
		if (mlx_image_to_window(cub3d->mlx, cub3d->torch_images[i - 1], \
								WIDTH - 300, HEIGHT - 650) == -1)
			close_program(cub3d, 1);
		cub3d->torch_images[i - 1]->instances->enabled = false;
		i++;
	}
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

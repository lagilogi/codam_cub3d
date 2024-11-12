/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 14:35:03 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/11/12 16:39:45 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	out_of_bounds(t_cub3d *cub3d, int y, int x)
{
	if (x < 0 || x >= cub3d->map.cols)
		return (true);
	if (y < 0 || y >= cub3d->map.rows)
		return (true);
	return (false);
}

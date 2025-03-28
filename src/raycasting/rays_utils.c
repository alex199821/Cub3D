/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 04:34:57 by macbook           #+#    #+#             */
/*   Updated: 2025/03/11 16:01:55 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

double	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

double	fixed_dist(double ray_x, double ray_y, t_game *game)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fix_dist;

	delta_x = ray_x - game->player_data->x;
	delta_y = ray_y - game->player_data->y;
	angle = atan2(delta_y, delta_x) - game->player_data->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

bool	check_wall(float px, float py, t_game *game)
{
	int	x;
	int	y;
	int	block_size;

	block_size = game->config->block_size;
	x = px / block_size;
	y = py / block_size;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

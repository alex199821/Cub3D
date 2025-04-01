/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_placement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:55:44 by auplisas          #+#    #+#             */
/*   Updated: 2025/04/01 19:32:06 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

uint32_t	fix_color(uint32_t color)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	red = color & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = (color >> 16) & 0xFF;
	alpha = (color >> 24) & 0xFF;
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

void	calculate_ray_x_hit(t_game *game, t_dda *dda)
{
	if (dda->hit_result->side == 0)
	{
		dda->hit_result->exact_hit_x = game->player_data->y
			/ game->config->block_size + dda->hit_result->perp_wall_dist
			* dda->ray->ray_dir_y;
	}
	else
	{
		dda->hit_result->exact_hit_x = game->player_data->x
			/ game->config->block_size + dda->hit_result->perp_wall_dist
			* dda->ray->ray_dir_x;
	}
	dda->hit_result->exact_hit_x = dda->hit_result->exact_hit_x
		- floor(dda->hit_result->exact_hit_x);
}

void	draw_wall_slice(t_game *game, int ray_x, t_dda *dda)
{
	mlx_texture_t	*tex;
	float			step;
	uint32_t		color;
	int				y;

	y = dda->draw->draw_start;
	if (dda->hit_result->side == 0)
	{
		if (dda->ray->ray_dir_x > 0)
			tex = game->texture_data->west_texture;
		else
			tex = game->texture_data->east_texture;
	}
	else
	{
		if (dda->ray->ray_dir_y > 0)
			tex = game->texture_data->north_texture;
		else
			tex = game->texture_data->south_texture;
	}
	step = 1.0 * tex->height / dda->draw->line_height;
	dda->draw->texture_vertical_pos = (y - game->config->s_height / 2
			+ dda->draw->line_height / 2) * step;
	calculate_ray_x_hit(game, dda);
	dda->draw->texture_horizontal_pos = (int)(dda->hit_result->exact_hit_x
			* tex->width);
	if ((dda->hit_result->side == 0 && dda->ray->ray_dir_x < 0)
		|| (dda->hit_result->side == 1 && dda->ray->ray_dir_y > 0))
		dda->draw->texture_horizontal_pos = tex->width
			- dda->draw->texture_horizontal_pos - 1;
	while (y < dda->draw->draw_end)
	{
		dda->draw->tex_y = (int)dda->draw->texture_vertical_pos % tex->height;
		color = fix_color(((uint32_t *)tex->pixels)[dda->draw->tex_y
				* tex->width + dda->draw->texture_horizontal_pos]);
		mlx_put_pixel(game->player_data->player, ray_x, y, color);
		dda->draw->texture_vertical_pos += step;
		y++;
	}
}

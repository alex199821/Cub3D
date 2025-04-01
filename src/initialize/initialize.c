/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/02 00:05:33 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../Includes/cub3d.h"

void	place_elements_on_map(t_game *game, int y, int x)
{
	int		block_size;

	block_size = game->config->block_size;
	if (game->map[y][x] == '1' && !game->debug_view)
		mlx_image_to_window(game->mlx, game->wall, x * block_size, y
			* block_size);
	if (game->map[y][x] == '0' && !game->debug_view)
		mlx_image_to_window(game->mlx, game->background, x * block_size, y
			* block_size);
	if (is_player_char(game->map[y][x]))
	{
		if (!game->debug_view)
			mlx_image_to_window(game->mlx, game->background, x * block_size, y
				* block_size);
		game->player_data->x = block_size * x + (block_size / 2);
		game->player_data->y = block_size * y + (block_size / 2);
	}
}

void	flood_map_items(t_game *game)
{
	int	y;
	int	x;
	int	block_size;

	block_size = game->config->block_size;
	game->background = mlx_new_image(game->mlx, block_size, block_size);
	game->wall = mlx_new_image(game->mlx, block_size, block_size);
	fill_image_pixels(game, game->background,
		(uint32_t)ft_pixel(game->ceiling_color->r, game->ceiling_color->g,
			game->ceiling_color->b, 255));
	fill_image_pixels(game, game->wall, (uint32_t)ft_pixel(game->floor_color->r,
			game->floor_color->g, game->floor_color->b, 255));
	y = 0;
	printf("Rows: %d\n", game->rows);
	printf("Columns: %d\n", game->columns);
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			place_elements_on_map(game, y, x);
			x++;
		}
		y++;
	}
}

//TODO too much random values, need to be changed
void	init_player(t_game *game, t_point *player_data)
{
	double	pi_value;

	pi_value = atan(1.0) * 4.0;
	player_data->angle_speed = ROTATION_SPEED;
	player_data->speed = PLAYER_SPEED;
	if (player_data->direction == 'N')
		player_data->angle = pi_value * 1.5f;
	if (player_data->direction == 'S')
		player_data->angle = pi_value * 0.5f;
	if (player_data->direction == 'W')
		player_data->angle = pi_value;
	if (player_data->direction == 'E')
		player_data->angle = pi_value * 2.0f;
	player_data->player = mlx_new_image(game->mlx,
			game->config->s_width, game->config->s_height);
}

t_game	*initialize_game_data(char *map_file)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->config = ft_calloc(1, sizeof(t_config));
	game->debug_view = INIT_DEBUG_VIEW;
	game->player_data = ft_calloc(1, sizeof(t_point));
	game->texture_data = ft_calloc(1, sizeof(t_textures));
	game->mlx = mlx_init(TMP_VALUE, TMP_VALUE, "Cub3D", true);
	mlx_get_monitor_size(0, &game->config->s_width, &game->config->s_height);
	mlx_terminate(game->mlx);
	game->mlx = \
		mlx_init(game->config->s_width, game->config->s_height, "Cub3D", true);
	game->map_file = map_file;
	parse_map(game);
	game->config->block_size = calculate_block_size(game->config->s_width,
			game->config->s_height, game->rows, game->columns);
	flood_map_items(game);
	init_player(game, game->player_data);
	return (game);
}

void	init_dda(t_dda *dda)
{
	dda->ray = (t_dda_ray *)ft_calloc(1, sizeof(t_dda_ray));
	dda->state = (t_dda_state *)ft_calloc(1, sizeof(t_dda_state));
	dda->hit_result = (t_hit_result *)ft_calloc(1, sizeof(t_hit_result));
	dda->draw = (t_drawing *)ft_calloc(1, sizeof(t_drawing));
}

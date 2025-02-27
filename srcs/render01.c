/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalinow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:01 by jkalinow          #+#    #+#             */
/*   Updated: 2025/02/15 18:43:06 by jkalinow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_screen(t_game *game, uint32_t background_color)
{
	int		total_pixels;
	int		i;
	char	*img_data;

	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->screen_width, \
		game->screen_height);
	img_data = mlx_get_data_addr(game->img, &(int){0}, &(int){0}, &(int){0});
	total_pixels = game->screen_width * game->screen_height;
	i = 0;
	while (i < total_pixels)
	{
		*(uint32_t *)(img_data + i * 4) = background_color;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	put_pixel(t_game *game, int x, int y, uint32_t color)
{
	if (x < 0 || x >= game->screen_width || y < 0 || y >= game->screen_height)
		return ;
	((uint32_t *)game->img_data)[y * game->screen_width + x] = color;
}

uint32_t	rgb_to_uint32(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	draw_ceiling(t_game *game, int x, int y)
{
	uint32_t	ceiling_color;
	int			red;
	int			green;
	int			blue;

	red = game->config.ceiling_color[0];
	green = game->config.ceiling_color[1];
	blue = game->config.ceiling_color[2];
	ceiling_color = rgb_to_uint32(red, green, blue);
	put_pixel(game, x, y, ceiling_color);
}

void	draw_floor(t_game *game, int x, int y)
{
	uint32_t	floor_color;
	int			red;
	int			green;
	int			blue;

	red = game->config.floor_color[0];
	green = game->config.floor_color[1];
	blue = game->config.floor_color[2];
	floor_color = rgb_to_uint32(red, green, blue);
	put_pixel(game, x, y, floor_color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:39:51 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 17:26:14 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

static	void	ft_get_sprite_val(t_vars *vars, t_sprite *sprite)
{
	float	screen_dist;
	float	ortho_dist;

	if (sprite->is_visible == 0)
		return ;
	sprite->hide_color = ft_get_xpm_pixel_value(&vars->text.sprite, 0, 0);
	screen_dist = (vars->win_width / 2) / tan(ft_radconvert(FOV / 2));
	sprite->angle = vars->player.angle;
	sprite->angle += atan2(sprite->y - vars->player.y,
			sprite->x - vars->player.x);
	sprite->angle = ft_within_twopi(sprite->angle);
	sprite->dist = ft_get_distance(vars->player.x, vars->player.y,
			sprite->x, sprite->y);
	ortho_dist = sprite->dist * cos(sprite->angle);
	sprite->height = (TILE_SIZE / ortho_dist) * screen_dist;
	sprite->width = sprite->height;
	sprite->start_y = (vars->win_height / 2) - (sprite->height / 2);
	sprite->end_y = (vars->win_height / 2) + (sprite->height / 2) - 1;
	sprite->left_x = (vars->win_width / 2) + tan(sprite->angle) * screen_dist;
	sprite->left_x -= sprite->width / 2;
	sprite->right_x = sprite->left_x + sprite->width - 1;
}

static	void	ft_sort_sprite_by_dist(t_vars *vars, t_sprite *sprite)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < vars->sprite_count - 1)
	{
		j = i;
		while (j < vars->sprite_count)
		{
			if (sprite[i].dist < sprite[j].dist)
			{
				tmp = sprite[j];
				sprite[j] = sprite[i];
				sprite[i] = tmp;
				i = 0;
			}
			j++;
		}
		i++;
	}
}

static	int		ft_s_color(t_vars *vars, t_sprite *sprite, int x, int y)
{
	int x_xpm;
	int y_xpm;
	int color;

	x_xpm = x / sprite->width * vars->text.sprite.width;
	y_xpm = y / sprite->height * vars->text.sprite.height;
	color = ft_get_xpm_pixel_value(&vars->text.sprite, x_xpm, y_xpm);
	return (color);
}

static	void	ft_draw_sprite(t_vars *vars, t_sprite *sprite,
		int x_offset, int y_offset)
{
	int x;
	int y;
	int y_sprite;
	int x_sprite;
	int sprite_color;

	x = sprite->left_x + x_offset;
	x_sprite = 0 + x_offset;
	while (x <= sprite->right_x && x < vars->win_width)
	{
		y_sprite = 0 + y_offset;
		y = sprite->start_y + y_offset;
		while (y <= sprite->end_y && y < vars->win_height)
		{
			sprite_color = ft_s_color(vars, sprite, x_sprite, y_sprite);
			if (sprite->dist < vars->rays[x].distance
					&& sprite_color != sprite->hide_color)
				my_mlx_pixel_put(vars, x, y, sprite_color);
			y_sprite++;
			y++;
		}
		x_sprite++;
		x++;
	}
}

void			ft_render_sprite(t_vars *vars)
{
	int i;
	int x_offset;
	int y_offset;

	i = 0;
	while (i < vars->sprite_count)
		ft_get_sprite_val(vars, &vars->sprite_tab[i++]);
	ft_sort_sprite_by_dist(vars, vars->sprite_tab);
	i = 0;
	while (i < vars->sprite_count)
	{
		y_offset = 0;
		x_offset = 0;
		if (vars->sprite_tab[i].is_visible)
		{
			while (vars->sprite_tab[i].left_x + x_offset < 0)
				x_offset++;
			while (vars->sprite_tab[i].start_y + y_offset < 0)
				y_offset++;
			ft_draw_sprite(vars, &vars->sprite_tab[i], x_offset, y_offset);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_hit_algebra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:27:05 by calao             #+#    #+#             */
/*   Updated: 2021/03/03 16:11:14 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"


void	ft_set_vert_hit(t_inter *vert, t_vars *vars, t_rays *ray)
{
	float x;
	float y;

	x = vars->player.x;
	y = vars->player.y;
	// Trouver une parade a INT_MAX
	vert->distance = INT_MAX;
	vert->found_wall = -1;
	vert->content = -1;

	//printf("vars->ray_num = %f\n", vars->ray_num);
	vert->x_inter = ((int)(x / TILE_SIZE)) * TILE_SIZE ;
	if (ray->rayisright)
		vert->x_inter += TILE_SIZE;
	vert->y_inter = y - (vert->x_inter - x) * tan(ray->angle);
	vert->x_step = TILE_SIZE;
	if (ray->rayisleft)
		vert->x_step *= -1;
	vert->y_step = TILE_SIZE * tan(ray->angle);
	if (ray->rayisup && vert->y_step > 0)
		vert->y_step *= -1;
	else if (ray->rayisdown && vert->y_step < 0)
		vert->y_step *= -1;
	vert->next_x = vert->x_inter;
	vert->next_y = vert->y_inter;
}

void	ft_set_horz_hit(t_inter *horz, t_vars *vars, t_rays *ray)
{
	float x;
	float y;

	x = vars->player.x;
	y = vars->player.y;
	// Trouver une parade a INT_MAX
	horz->distance = INT_MAX;
	horz->found_wall = -1;
	horz->content = -1;
	horz->y_inter = ((int)(y / TILE_SIZE)) * TILE_SIZE ;
	if (ray->rayisdown)
		horz->y_inter += TILE_SIZE;
	horz->x_inter = x - (horz->y_inter - y) / tan(ray->angle);
	horz->y_step = TILE_SIZE;
	if (ray->rayisup)
		horz->y_step *= -1;
	horz->x_step = TILE_SIZE / tan(ray->angle);
	if (ray->rayisleft && horz->x_step > 0)
		horz->x_step *= -1;
	else if (ray->rayisright && horz->x_step < 0)
		horz->x_step *= -1;
	horz->next_x = horz->x_inter;
	horz->next_y = horz->y_inter;
}

void	ft_find_horz_wallhit(t_vars *vars, t_rays *ray, t_inter *horz)
{
	float tmp;
	float x1;
	float y1;

	x1 = vars->player.x;
	y1 = vars->player.y;
	tmp = 0;
	if (ray->rayisup)
		tmp = -1;
	while (!ft_is_maplimit(horz->next_x, horz->next_y + tmp, vars))
	{
	//	printf("ray->rayisup = %d\n", ray->rayisup);
		//printf("HORZ_X = %f | HORZ_Y %f\n", horz->next_x, horz->next_y);
		if (ft_is_wall(horz->next_x, horz->next_y + tmp, vars))
		{
			horz->wallhitx = horz->next_x;
			horz->wallhity = horz->next_y;
			horz->content = ft_map_content(horz->next_x, horz->next_y + tmp, vars);
			horz->distance = ft_get_distance(x1, y1, horz->next_x, horz->next_y);
			horz->found_wall = 1;
		//	printf("FINAL HORZ_X = %f | HORZ_Y %f\n", horz->next_x, horz->next_y);
			return;
		}
		horz->next_x += horz->x_step;
		horz->next_y += horz->y_step;
	}
}

void	ft_find_vert_wallhit(t_vars *vars, t_rays *ray, t_inter *vert)
{
	float tmp;
	float x1;
	float y1;

	x1 = vars->player.x;
	y1 = vars->player.y;
	tmp = 0;
	if (ray->rayisleft)
		tmp = -1;
	while (!ft_is_maplimit(vert->next_x + tmp, vert->next_y, vars))
	{
		//printf("VERT_X = %f | VERT_Y %f\n", vert->next_x, vert->next_y);
		//SEGV cause de ft_is_wall et ft_map_content
		if (ft_is_wall(vert->next_x + tmp, vert->next_y, vars))
		{
			vert->wallhitx = vert->next_x;
			vert->wallhity = vert->next_y;
			vert->content = ft_map_content(vert->next_x + tmp, vert->next_y, vars);
			vert->distance = ft_get_distance(x1, y1, vert->next_x, vert->next_y);
			vert->found_wall = 1;
		//	printf("FINAL: VERT_X = %f | VERT_Y %f\n", vert->next_x, vert->next_y);
	//		printf("FOUND INTERSECTION\n");
			return;
		}
		vert->next_x += vert->x_step;
		vert->next_y += vert->y_step;
	}
	//printf("no intersection found\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:29:51 by calao             #+#    #+#             */
/*   Updated: 2021/03/15 15:00:06 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int			ft_parsing_args(t_vars *vars, int argc, char **argv)
{
	vars->bmp_save = 0;
	if (argc < 2 || argc > 3)
	{
		printf("Error\nUsage : 1 or 2 arguments\n");
		return (1);
	}
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
		{
			printf("Error\n: second argument must be \"--save\"\n");
			return (1);
		}
		vars->bmp_save = 1;
	}
	return (0);
}

void		ft_start_game(t_vars *vars)
{
	if (vars->bmp_save)
	{
		ft_cast_all_rays(vars);
		ft_render_minimap(vars);
		ft_render_sprite(vars);
		ft_save_bmp(vars);
	}
	else
	{
		mlx_hook(vars->win, 33, 1L << 17, &mlx_loop_end, vars->mlx);
		mlx_hook(vars->win, 2, 1L << 0, ft_update_move, vars);
		mlx_hook(vars->win, 3, 1L << 1, ft_reset_player, vars);
		mlx_loop_hook(vars->mlx, ft_update_screen, vars);
		mlx_loop(vars->mlx);
	}
}

int			main(int argc, char **argv)
{
	t_vars		vars;

	ft_game_null_init(&vars);
	if (ft_parsing_args(&vars, argc, argv)
			|| ft_parsing_main(argv[1], &vars.cube))
	{
		ft_free_game(&vars);
		return (-1);
	}
	if (ft_init_game(&vars.cube, &vars))
	{
		ft_free_game(&vars);
		printf("Error\n Initializing game structures failes.\n");
		return (-1);
	}
	ft_start_game(&vars);
	ft_free_game(&vars);
	return (0);
}

int			ft_update_screen(t_vars *vars)
{
	ft_update_player(vars);
	ft_cast_all_rays(vars);
	ft_render_sprite(vars);
	ft_render_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->game.img, 0, 0);
	ft_reset_sprites_visibility(vars, vars->sprite_count);
	return (0);
}

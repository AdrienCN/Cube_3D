#include "h_cube.h"


#define KEYPRESS	1L<<0
#define KEYRELEASE	1L<<1

int				ft_parsing_args(t_vars *vars, int argc, char **argv)
{
	vars->bmp_save = 0;
	if (argc < 2 || argc > 3)
	{
		printf("Usage : 1 or 2 arguments\n");
		return (1);
	}
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
		{
			printf("Error: second argument must be \"--save\"\n");
			return (1);
		}
		vars->bmp_save = 1;
	}
	return (0);
}
void			ft_start_game(t_vars *vars)
{
	if (vars->bmp_save)
	{
		ft_cast_all_rays(vars);
		ft_render_walls(vars, vars->rays);
		ft_render_sprite(vars);
		ft_save_bmp(vars);
	}
	else
	{
		//implementer croix rouge
		mlx_loop_hook(vars->mlx, ft_update_screen, vars);
		mlx_hook(vars->win, 2, KEYPRESS, ft_update_move, vars);
		mlx_hook(vars->win, 3, KEYRELEASE, ft_reset_player, vars);
		mlx_loop(vars->mlx);
	}
}

int             main(int argc, char **argv)
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
		printf("Error while initializing game structures.\n");
		return (1);
	}
		
	printf("Init ok\n");
	ft_start_game(&vars);
	printf("before freeing the game\n");
	ft_free_game(&vars);
	printf("\nmain --> return (0);\n");
	return (0);
}

int		ft_update_screen(t_vars *vars)
{
	ft_cast_all_rays(vars);
	
	// draw 3D cube with my_mlx_pixel_put
	ft_render_walls(vars, vars->rays);

	ft_render_sprite(vars);
	
	// Draw minimap + rays
	//ft_render_minimap(vars);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->game.img, 0, 0);
	ft_reset_sprites_visibility(vars, vars->sprite_count);
	return (0);
}

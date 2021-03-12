/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/03/12 22:57:13 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int		ft_parsing_main(char *map_file_name, t_cube *cube)
{
	int			fd;
	int			error;

	if ((error = ft_check_file_ext_name(map_file_name, ".cub")))
		return (ft_parsing_error_msg(1, -4));
	if ((error = ft_is_file_readable(map_file_name)))
		return (ft_parsing_error_msg(1, error));
	if ((fd = open(map_file_name, O_RDONLY)) < 0)
		return (ft_parsing_error_msg(1, -1));
	if ((error = ft_first_parsing(fd, cube)))
		return (ft_parsing_error_msg(2, error));
	if ((error = ft_second_parsing(fd, cube)))
		return (ft_parsing_error_msg(3, error));
	if ((error = close(fd)) < 0)
		return(ft_parsing_error_msg(1, -3));
	printf("--------------after-------------------\n");
	ft_print_mapinfo(cube);
	printf("----------------------------------\n");
	return (0);
}

void	ft_cube_null_init(t_cube *element)
{
	//Supprimer les int qui ne sont pas des BOL ? sauf sprite count?
	element->sprite_count = 0;
	element->r_bol = 0;
	element->r_x = 0;
	element->r_y = 0;
	element->north = NULL;
	element->east = NULL;
	element->south = NULL;
	element->west = NULL;
	element->sprite = NULL;
	element->floor.state = 0;
	element->floor.r = 0;
	element->floor.g = 0;
	element->floor.b = 0;
	element->player_tmp.cardinal = '0';
	element->player_tmp.x = 0;
	element->player_tmp.y = 0;
	element->ceil.state = 0;
	element->ceil.r = 0;
	element->ceil.g = 0;
	element->ceil.b = 0;
	element->map = NULL;
	element->gnl_line = NULL;
	element->m_line = NULL;
	element->map_start = TRUE;
	element->map_end = FALSE;
	element->max_row = 0;
	element->max_col = 0;
	element->info_nbr = 0;
}

void ft_print_mapinfo(t_cube *element)
{
	int i;

	printf("r_bol = %d\n", element->r_bol);
	printf("r_x = %d | r_y = %d\n", element->r_x, element->r_y); 
	printf("no = %s \n", element->north); 
	printf("ea = %s \n", element->east);
	printf("so = %s \n", element->south);
	printf("we = %s \n", element->west);
	printf("sprite = %s \n", element->sprite);
	printf("floor.state = %d\n", element->floor.state);
	printf("floor RGB [%d,%d,%d] \n", element->floor.r, element->floor.g, element->floor.b);
	printf("ceiling.state = %d\n", element->ceil.state);
	printf("ceiling RGB [%d,%d,%d] \n", element->ceil.r, element->ceil.g, element->ceil.b);
	printf("_____Player___:\n");
	printf("Orientation = %c | X = %f | Y = %f\n",
		   	element->player_tmp.cardinal, element->player_tmp.x, element->player_tmp.y);
	printf("max_row = %d\n", element->max_row);
	printf("max_col = %d\n", element->max_col);
	printf("m_line = {%s}\n", element->m_line);
	printf("gnl_line = [%s]\n", element->gnl_line);
	printf("sprite_count = %d\n", element->sprite_count);
	if (element->map == NULL)
		printf("element->map = (null)\n");
	else
	{
		printf("______________MAP_______________:\n");
		i = 0;
		printf("col:--|");
		while (i < element->max_col)
		{
			printf("%d|", i);
			i++;
		}
		printf("\n____________________________:\n");
		ft_print_tab(element->map);
	}
}


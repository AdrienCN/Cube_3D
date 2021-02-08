/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:18:20 by calao             #+#    #+#             */
/*   Updated: 2021/02/08 10:28:53 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_cube.h"

int		ft_parsing_main(char *map_file, t_cube *map_info)
{
	int			fd;

	ft_mapinfo_init(map_info);
	if (ft_check_filename(map_file, ".cub")
			|| (fd = open(map_file, O_RDONLY)) < 0 
			|| ft_first_parsing(fd, map_info) == -1
			|| ft_second_parsing(fd, map_info) == -1
		   	|| close(fd) < 0)
	{
		printf("...ERROR....Map_info value: \n");
		ft_print_mapinfo(map_info);
		ft_free_mapinfo(map_info);
		printf("\n...program SHUT DOWN...\n");
		return(1);
	}
	printf("--------------after-------------------\n");
	ft_print_mapinfo(map_info);
	printf("----------------------------------\n");
	return (0);
}


void	ft_free_doublearray(char **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
}

void	ft_free_mapinfo(t_cube *element)
{
	if (element->north != NULL)
		free(element->north);
	if (element->east != NULL)
		free(element->east);
	if (element->south != NULL)
		free(element->south);
	if (element->west != NULL)
		free(element->west);
	if (element->sprite != NULL)
		free(element->sprite);
	if (element->map != NULL)
	{
		ft_free_doublearray(element->map);
		free(element->map);
	}
	if (element->gnl_line != NULL)
		free(element->gnl_line);
	if (element->m_line != NULL)
		free(element->m_line);
}

void	ft_mapinfo_init(t_cube *element)
{
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
	element->ceil.state = 0;
	element->ceil.r = 0;
	element->ceil.g = 0;
	element->ceil.b = 0;
	element->player = '0';
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
	int y;

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
	printf("Player_Orientation = %c\n", element->player);
	printf("max_row = %d\n", element->max_row);
	printf("max_col = %d\n", element->max_col);
	printf("m_line = {%s}\n", element->m_line);
	printf("gnl_line = [%s]\n", element->gnl_line);
	if (element->map == NULL)
		printf("element->map = (null)\n");
	else
	{
		printf("______________MAP_______________:\n");
		i = 0;
		while (element->map[i])
		{
			y = 0;
			printf("%.2d --  |", i);
			while (element->map[i][y] != '\0')
			{
				printf("%c", element->map[i][y]);
				y++;
			}
			printf("|\n");
			i++;
		}
	}
}

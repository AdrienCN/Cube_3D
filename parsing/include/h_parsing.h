#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_rgb
{
	int state;
	int r;
	int g;
	int b;
}			t_rgb;

typedef struct s_cube
{
	int r_bol;
	int r_x;
	int r_y;
	char *north;
	char *east;
	char *west;
	char *south;
	char *sprite;
	t_rgb floor;
	t_rgb ceil;
	char player;
	int info_nbr;
}				t_cube;
		//FIRST PARSING//
int		ft_first_parsing(int fd, t_cube *map_info);
int		ft_try_assigning_value(char *line, t_cube *map_info);
int		ft_assign_resolution(t_cube *element, char *line);
int		ft_check_filename(char *filename, char *ext_name);
int		ft_check_mapname(char *name);

int		ft_rbg_rb_format(char *line);
int		ft_rgb_assign(int arrow, t_cube *map_info, char *line);
int		ft_rgb_check_format(char *line);
int		ft_rgb_g_format(char *line);
int		ft_rgb_give_val(t_rgb *ceiloor, char *line);

int		ft_text_assign(int arrow, t_cube *map_info, char *line);
int		ft_text_check_format(char *path);
int		ft_text_give_val(char **text, char *path);
char 	*ft_text_check_path(char *path);

		//SECOND PARSING//
int		ft_second_parsing(int fd, t_cube *map_info);


		//MAIN_PARSING//
void	ft_mapinfo_init(t_cube *element);
void	ft_print_mapinfo(t_cube *element);

#endif

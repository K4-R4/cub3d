/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_to_world.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:46:31 by tokazaki          #+#    #+#             */
/*   Updated: 2023/11/08 19:48:45 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_floor_or_ceiling(char *line);
static int	create_rgb(int red, int green, int blue);

void	set_color_to_world(char	*line, t_world *world)
{
	int	i;
	int	rgb[3];
	int	color;
	int	ceiling_or_floor;

	i = 0;
	color = 0;
	ceiling_or_floor = check_floor_or_ceiling(line);
	line = skip_space(&line[2]);
	while (line != NULL)
	{
		rgb[i] = ft_atoi(line);
		line = ft_strchr(line, ',');
		if (line == NULL)
			break ;
		line++;
		i++;
	}
	color = create_rgb(rgb[0], rgb[1], rgb[2]);
	if (ceiling_or_floor == 'C' && world->ceiling_color == 0)
		world->ceiling_color = color;
	else if (ceiling_or_floor == 'F' && world->floor_color == 0)
		world->floor_color = color;
	else
		error_exit_msg("同じ天井・地面の色が複数回指定されているよ");
}
//	ft_dprintf(1, "[%s]\n", line);

static int	create_rgb(int red, int green, int blue)
{
	int	color;

	color = (red << 16 | green << 8 | blue);
	return (color);
}

static int	check_floor_or_ceiling(char *line)
{
	int	direction;

	direction = INIT;
	if (strncmp("F ", line, 2) == 0)
		direction = 'F';
	if (strncmp("C ", line, 2) == 0)
		direction = 'C';
	return (direction);
}

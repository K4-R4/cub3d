/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:53:38 by tkuramot          #+#    #+#             */
/*   Updated: 2023/11/07 17:08:23 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_world(t_world *world);
static int	checke_file_name(char *file);

void	get_config(char *argv[], t_world *world)
{
	int	open_fd;

	open_fd = checke_file_name(argv[1]);
	set_texture(open_fd, world);
	set_color(open_fd, world);
	set_map(open_fd, world);
	close(open_fd);
	check_map(world);
	print_world(world);
}

//ファイル名の確認
static int	checke_file_name(char *file)
{
	int		open_fd;
	char	*line;

	line = ft_strrchr(file, '.');
	if (line == NULL || ft_strcmp(line, ".cub") != 0)
		error_exit_msg("ファイル名間違ってるよ。");
	open_fd = open(file, O_DIRECTORY);
	if (0 < open_fd)
		error_exit_msg("これ、ディレクトリだよ");
	errno = 0;
	open_fd = open(file, O_RDONLY);
	if (open_fd < 0)
		error_exit_msg("Please enter the correct file");
	return (open_fd);
}
//	ft_dprintf(1, "line:%s/file:%s", line, file);

static void	print_world(t_world *world)
{
	int	i;
	int	fd;

	ft_dprintf(1, "----- texture -----\n");
	ft_dprintf(1, "%s\n", world->texture.north_texture);
	ft_dprintf(1, "%s\n", world->texture.south_texture);
	ft_dprintf(1, "%s\n", world->texture.west_texture);
	ft_dprintf(1, "%s\n", world->texture.east_texture);
	ft_dprintf(1, "\n----- color -----\n");
	ft_dprintf(1, "[Floor: %x]\n", world->floor_color);
	ft_dprintf(1, "[Ceiling: %x]\n", world->ceiling_color);
	ft_dprintf(1, "\n----- map -----\n");
	i = 0;
	while (world->map[i][0] != '\0')
	{
		ft_dprintf(1, "|%s|\n", world->map[i]);
		i++;
	}
	fd = open(world->texture.north_texture, O_RDONLY);
	ft_dprintf(2, "northfileの中身：%s", get_next_line(fd));
}

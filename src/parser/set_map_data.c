/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:08:38 by tokazaki          #+#    #+#             */
/*   Updated: 2023/11/08 20:05:32 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	read_map(int fd, t_world *world, t_list **lst);
void		print_list(void *line);

void	set_map(int fd, t_world *world)
{
	t_list	*lst;

	read_map(fd, world, &lst);
	arrange_map_lst_to_ptr(world, lst);
	ft_lstclear(&lst, free);
}

//mapを読み込んで、線形リストにする
static void	read_map(int fd, t_world *world, t_list **lst)
{
	char	*line;

	line = read_file(fd);
	if (line == NULL)
		error_exit_msg("mapがないよ");
	del_newline_cord(line);
	*lst = ft_lstnew(line);
	while (1)
	{
		line = get_next_line(fd);
		if (errno != 0)
			error_exit_msg("mallocに失敗してたお");
		if (line == NULL)
			break ;
		del_newline_cord(line);
		ft_lstadd_back(lst, ft_lstnew(line));
	}
	(void)world;
}

//debug用
//	ft_dprintf(1, "-----set_map-----\n");
//	ft_lstiter(lst, print_list);
void	print_list(void *line)
{
	ft_dprintf(1, "[%s]\n", (char *)line);
}

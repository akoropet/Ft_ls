/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:37:06 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/16 16:19:23 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	open_dir_rec(t_data *data, char *d, char *path)
{
	t_file	*file;
	DIR		*dir;
	t_file	*tmp;

	file = NULL;
	path = ft_strjoin(path, d);
	ft_strcmp("", d) ? ft_printf("\n%s:\n", path) : 0;
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_strfjoin(path, "/", 1);
	(dir = opendir(path)) ? read_files(data, &file, dir, path) : error(d, 0);
	file = print_list(data, file);
	tmp = file;
	while (file)
	{
		file->type == 'd' && ft_strcmp(".", file->name) &&
			ft_strcmp("..", file->name) ?
			open_dir_rec(data, file->name, path) : 0;
		file = file->next;
	}
	ft_strdel(&path);
	ft_clear_file(tmp);
}

void	open_dir(t_data *data, char *path)
{
	t_file	*file;
	DIR		*dir;

	file = NULL;
	if (ft_strcmp("-", path) && path[ft_strlen(path) - 1] != '/')
		path = ft_strfjoin(path, "/", 1);
	if ((dir = opendir(path)))
		read_files(data, &file, dir, path);
	else
	{
		error(path, 0);
		ft_strdel(&path);
		return ;
	}
	file = print_list(data, file);
	ft_clear_file(file);
	ft_strdel(&path);
}

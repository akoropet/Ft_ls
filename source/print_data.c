/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:35:26 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/16 16:33:56 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_file	*print_list(t_data *data, t_file *file)
{
	t_file	*tmp;

	ft_sort(data, &file);
	tmp = file;
	while (file)
	{
		if (data->l_flag && data->a_flag)
			ft_printf("%c%s%4d %s %s %6s %s %s\n", file->type, file->mode,
				file->link, file->user, file->group, file->size, file->date,
				file->name);
		else if (data->l_flag && !data->a_flag && file->name[0] != '.')
			ft_printf("%c%s%4d %s %s %6s %s %s\n", file->type, file->mode,
				file->link, file->user, file->group, file->size, file->date,
				file->name);
		else if (!data->l_flag && data->a_flag)
			ft_printf("%s\n", file->name);
		else if (!data->l_flag && !data->a_flag && file->name[0] != '.')
			ft_printf("%s\n", file->name);
		file = file->next;
	}
	return (tmp);
}


void	print_err(t_data *data)
{
	t_file	*err;
	DIR		*dir;

	err = data->err;
	sort_file(&err, NULL, NULL);
	data->err = err;
	while (err)
	{
		dir = opendir(err->name);
		error(err->name, 0);
		errno = 0;
		err = err->next;
	}
}

void	print_file(t_data *data)
{
	t_file	*file;

	file = data->file;
	file = print_list(data, file);
	ft_clear_file(file);
}

void	print_dir(t_data *data)
{
	t_file	*dir;

	dir = data->dir;
	sort_file(&dir, NULL, NULL);
	data->dir = dir;
	while (dir)
	{
		if (data->file)
			ft_putendl("");
		if (data->err || data->file)
			ft_printf("%s:\n", dir->name);
		data->rec_flag ? open_dir_rec(data, "", dir->name) :
			open_dir(data, dir->name);
		dir = dir->next;
	}
}

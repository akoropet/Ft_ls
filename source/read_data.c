/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:31:54 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/16 16:19:28 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	several_path(t_data *data, int ac, char **av, int i)
{
	t_file			*file;
	struct stat		stat_dir;

	file = NULL;
	while (i < ac)
	{
		if ((data->l_flag && !(lstat(av[i], &stat_dir)) &&
			S_ISDIR(stat_dir.st_mode & S_IFMT)) || (!data->l_flag &&
			!(stat(av[i], &stat_dir)) && S_ISDIR(stat_dir.st_mode & S_IFMT)))
			add_dir(data, av[i]);
		else if (!(lstat(av[i], &stat_dir)))
			add_file(data, av[i]);
		else
			add_err(data, av[i]);
		i++;
	}
	print_err(data);
	print_file(data);
	print_dir(data);
}

void	read_arg(t_data *data, int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1] != '\0' &&
		ft_strcmp("--", av[i]))
		if (!flag_parcer(data, av[i]))
			break ;
	if (av[i] && !ft_strcmp("--", av[i]))
		i++;
	if (av[i] && !ft_strcmp("-", av[i]) && i == ac - 1)
		open_dir(data, ft_strdup("-"));
	if (errno)
		return ;
	else if (!data->rec_flag && i == ac)
		open_dir(data, ft_strdup("./"));
	else if (data->rec_flag && i == ac)
		open_dir_rec(data, "", ("."));
	else
		several_path(data, ac, av, i);
}

void	read_files(t_data *data, t_file **file, DIR *dir, char *path)
{
	struct dirent	*read_dir;
	struct stat		stat_dir;
	int				i;
	char			*tmp;

	i = 0;
	tmp = NULL;
	while ((read_dir = readdir(dir)) && ++i)
	{
		path ? tmp = ft_strjoin(path, read_dir->d_name) : 0;
		tmp ? lstat(tmp, &stat_dir) : lstat(path, &stat_dir);
		ft_strdel(&tmp);
		while ((*file))
			file = &(*file)->next;
		(*file) = (t_file *)malloc(sizeof(t_file));
		(*file)->next = NULL;
		(*file)->name = ft_strdup(read_dir->d_name);
		create_info(file, stat_dir);
		if ((!data->a_flag && (*file)->name[0] != '.') || data->a_flag)
			data->total += stat_dir.st_blocks;
	}
	closedir(dir);
	if (((i > 2 && !data->a_flag) || data->a_flag) && data->l_flag)
		ft_printf("total %d\n", data->total);
	data->total = 0;
}

void	create_info(t_file **file, struct stat stat_dir)
{
	(*file)->type = ft_type(stat_dir.st_mode);
	(*file)->mode = ft_mode(stat_dir.st_mode);
	(*file)->link = stat_dir.st_nlink;
	(*file)->user = ft_user(stat_dir.st_uid);
	(*file)->group = ft_group(stat_dir.st_gid);
	if ((*file)->type == 'c' || (*file)->type == 'b')
	{
		(*file)->size = ft_itoa(major(stat_dir.st_rdev));
		(*file)->size = ft_strfjoin((*file)->size, ", ", 1);
		(*file)->size = ft_strfjoin((*file)->size,
			ft_itoa(minor(stat_dir.st_rdev)), 3);
	}
	else
		(*file)->size = ft_itoa(stat_dir.st_size);
	(*file)->time = stat_dir.st_mtime;
	(*file)->date = ft_time(stat_dir);
}

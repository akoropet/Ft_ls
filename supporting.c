/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:40:40 by akoropet          #+#    #+#             */
/*   Updated: 2019/04/29 21:50:13 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		error(char *str, char sym)
{
	if (!str)
	{
		ft_printf("ft_ls: illegal option -- %c\n", sym);
		ft_printf("usage: ft_ls [-Ralrt] [file ...]\n");
		errno = 1;
		return (0);
	}
	else
	{
		ft_printf("ft_ls: %s: %s\n", str, strerror(errno));
		return (0);
	}
	return (1);
}

int		flag_parcer(t_data *data, char *av)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (av[i] == 'l')
			data->l_flag = 1;
		else if (av[i] == 'R')
			data->rec_flag = 1;
		else if (av[i] == 'a')
			data->a_flag = 1;
		else if (av[i] == 'r')
			data->rev_flag = 1;
		else if (av[i] == 't')
			data->t_flag = 1;
		else
			return (error(NULL, av[i]));
	}
	return (1);
}

void	ft_clear_file(t_file *file)
{
	t_file	*r;

	r = file;
	while (r)
	{
		file = r;
		r = r->next;
		ft_strdel(&file->mode);
		ft_strdel(&file->user);
		ft_strdel(&file->group);
		ft_strdel(&file->size);
		ft_strdel(&file->date);
		ft_strdel(&file->name);
		free(file);
	}
}

void	ft_sort(t_data *data, t_file **file)
{
	if (!data->t_flag && !data->rev_flag)
		sort_file(file, NULL, NULL);
	else if (!data->t_flag && data->rev_flag)
		sort_file_reverse(file, NULL, NULL);
	else if (data->t_flag && !data->rev_flag)
		sort_time(file, NULL, NULL);
	else if (data->t_flag && data->rev_flag)
		sort_time_reverse(file, NULL, NULL);
}

void	reset(t_data *data)
{
	data->l_flag = 0;
	data->rec_flag = 0;
	data->a_flag = 0;
	data->rev_flag = 0;
	data->t_flag = 0;
	data->file = NULL;
	data->dir = NULL;
	data->err = NULL;
	data->total = 0;
}

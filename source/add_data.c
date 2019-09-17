/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:38:34 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/16 16:19:15 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	add_dir(t_data *data, char *av)
{
	t_file	**dir;

	dir = &(data)->dir;
	while ((*dir))
		dir = &(*dir)->next;
	(*dir) = (t_file *)malloc(sizeof(t_file));
	(*dir)->next = NULL;
	(*dir)->name = ft_strdup(av);
	(*dir)->mode = NULL;
	(*dir)->user = NULL;
	(*dir)->group = NULL;
	(*dir)->size = NULL;
	(*dir)->date = NULL;
}

void	add_err(t_data *data, char *av)
{
	t_file	**err;

	err = &(data)->err;
	while ((*err))
		err = &(*err)->next;
	(*err) = (t_file *)malloc(sizeof(t_file));
	(*err)->next = NULL;
	(*err)->name = ft_strdup(av);
	(*err)->mode = NULL;
	(*err)->user = NULL;
	(*err)->group = NULL;
	(*err)->size = NULL;
	(*err)->date = NULL;
}

void	add_file(t_data *data, char *av)
{
	struct stat		stat_dir;
	t_file			**file;

	file = &(data)->file;
	while ((*file))
		file = &(*file)->next;
	(*file) = (t_file *)malloc(sizeof(t_file));
	(*file)->next = NULL;
	lstat(av, &stat_dir);
	(*file)->name = ft_strdup(av);
	create_info(file, stat_dir);
}

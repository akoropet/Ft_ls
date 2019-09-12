/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:27:12 by akoropet          #+#    #+#             */
/*   Updated: 2019/04/29 21:32:48 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*swap_list(t_file **prev1, t_file **prev2, t_file **f1, t_file **f2)
{
	if ((*prev1))
		(*prev1)->next = (*f2);
	(*prev2)->next = (*f2)->next;
	(*f2)->next = (*f1);
	if ((*prev1))
		return ((*prev1));
	return ((*f2));
}

void	sort_file(t_file **file, t_file *prev1, t_file *prev2)
{
	t_file	*f1;
	t_file	*f2;

	f1 = (*file);
	while (f1)
	{
		f2 = f1;
		while (f2)
		{
			if (ft_strcmp(f1->name, f2->name) > 0)
			{
				f1 = swap_list(&prev1, &prev2, &f1, &f2);
				!prev1 ? (*file) = f1 : 0;
				prev1 = NULL;
				prev2 = NULL;
			}
			if (f2->next)
				prev2 = f2;
			f2 = f2->next;
		}
		if (f1->next)
			prev1 = f1;
		f1 = f1->next;
	}
}

void	sort_file_reverse(t_file **file, t_file *prev1, t_file *prev2)
{
	t_file	*f1;
	t_file	*f2;

	f1 = (*file);
	while (f1)
	{
		f2 = f1;
		while (f2)
		{
			if (ft_strcmp(f1->name, f2->name) < 0)
			{
				f1 = swap_list(&prev1, &prev2, &f1, &f2);
				!prev1 ? (*file) = f1 : 0;
				prev1 = NULL;
				prev2 = NULL;
			}
			if (f2->next)
				prev2 = f2;
			f2 = f2->next;
		}
		if (f1->next)
			prev1 = f1;
		f1 = f1->next;
	}
}

void	sort_time(t_file **file, t_file *prev1, t_file *prev2)
{
	t_file	*f1;
	t_file	*f2;

	f1 = (*file);
	while (f1)
	{
		f2 = f1;
		while (f2)
		{
			if (f1->time < f2->time)
			{
				f1 = swap_list(&prev1, &prev2, &f1, &f2);
				!prev1 ? (*file) = f1 : 0;
				prev1 = NULL;
				prev2 = NULL;
			}
			if (f2->next)
				prev2 = f2;
			f2 = f2->next;
		}
		if (f1->next)
			prev1 = f1;
		f1 = f1->next;
	}
}

void	sort_time_reverse(t_file **file, t_file *prev1, t_file *prev2)
{
	t_file	*f1;
	t_file	*f2;

	f1 = (*file);
	while (f1)
	{
		f2 = f1;
		while (f2)
		{
			if (f1->time > f2->time)
			{
				f1 = swap_list(&prev1, &prev2, &f1, &f2);
				!prev1 ? (*file) = f1 : 0;
				prev1 = NULL;
				prev2 = NULL;
			}
			if (f2->next)
				prev2 = f2;
			f2 = f2->next;
		}
		if (f1->next)
			prev1 = f1;
		f1 = f1->next;
	}
}

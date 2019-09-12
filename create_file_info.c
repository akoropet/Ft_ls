/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 21:32:33 by akoropet          #+#    #+#             */
/*   Updated: 2019/04/29 21:34:39 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	ft_type(mode_t st_mode)
{
	char	sym;

	sym = '-';
	if (S_ISLNK(st_mode & S_IFMT))
		sym = 'l';
	else if (S_ISDIR(st_mode & S_IFMT))
		sym = 'd';
	else if (S_ISBLK(st_mode & S_IFMT))
		sym = 'b';
	else if (S_ISCHR(st_mode & S_IFMT))
		sym = 'c';
	else if (S_ISFIFO(st_mode & S_IFMT))
		sym = 'p';
	else if (S_ISSOCK(st_mode & S_IFMT))
		sym = 's';
	return (sym);
}

char	*ft_mode(mode_t st_mode)
{
	char	*mode;
	char	*num;
	char	*res;
	int		i;

	i = 0;
	mode = ft_strdup("rwxrwxrwx");
	num = ft_itoa_base(st_mode, 2);
	res = num + ft_strlen(num) - 9;
	while (mode[i])
	{
		if (res[i] && res[i] == '0')
			mode[i] = '-';
		i++;
	}
	ft_strdel(&num);
	return (mode);
}

char	*ft_user(uid_t st_uid)
{
	struct passwd	*user;

	user = getpwuid(st_uid);
	return (ft_strdup(user->pw_name));
}

char	*ft_group(gid_t st_gid)
{
	struct group	*group;

	group = getgrgid(st_gid);
	return (ft_strdup(group->gr_name));
}

char	*ft_time(struct stat stat_dir)
{
	char	*set;
	char	t_str[64];

	set = setlocale(LC_ALL, NULL);
	strftime(t_str, sizeof(t_str), "%b %e %H:%M",
		localtime(&stat_dir.st_mtime));
	return (ft_strdup(t_str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:52:08 by akoropet          #+#    #+#             */
/*   Updated: 2019/09/16 15:47:07 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/libft/libft.h"
# include <limits.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct		s_file
{
	char			type;
	char			*mode;
	int				link;
	char			*user;
	char			*group;
	char			*size;
	int				time;
	char			*date;
	char			*name;
	struct s_file	*next;
}					t_file;

typedef struct		s_data
{
	int				l_flag;
	int				rec_flag;
	int				a_flag;
	int				rev_flag;
	int				t_flag;
	int				total;
	t_file			*file;
	t_file			*dir;
	t_file			*err;
}					t_data;

void				sort_file(t_file **file, t_file *prev1, t_file *prev2);
void				sort_time(t_file **file, t_file *prev1, t_file *prev2);
t_file				*swap_list(t_file **prev1, t_file **prev2, t_file **f1,
	t_file **f2);
void				sort_file_reverse(t_file **file, t_file *prev1,
	t_file *prev2);
void				sort_time_reverse(t_file **file, t_file *prev1,
	t_file *prev2);

char				ft_type(mode_t st_mode);
char				*ft_mode(mode_t st_mode);
char				*ft_user(uid_t st_uid);
char				*ft_group(gid_t st_gid);
char				*ft_time(struct stat stat_dir);

void				several_path(t_data *data, int ac, char **av, int i);
void				read_arg(t_data *data, int ac, char **av);
void				create_info(t_file **file, struct stat stat_dir);
void				read_files(t_data *data, t_file **file, DIR *dir,
	char *path);

t_file				*print_list(t_data *data, t_file *file);
void				print_err(t_data *data);
void				print_file(t_data *data);
void				print_dir(t_data *data);

void				open_dir_rec(t_data *data, char *d, char *path);
void				open_dir(t_data *data, char *path);

void				add_dir(t_data *data, char *av);
void				add_err(t_data *data, char *av);
void				add_file(t_data *data, char *av);

int					error(char *str, char sym);
int					flag_parcer(t_data *data, char *av);
void				ft_clear_file(t_file *file);
void				ft_sort(t_data *data, t_file **file);
void				reset(t_data *data);

#endif

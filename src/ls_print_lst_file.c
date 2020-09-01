/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/09/01 19:06:16 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

void		ls_print_l(t_lst_file *lst, t_ls *obj)
{
	char	*perms;
	char	*t;

	printf("total %d\n", ls_file_get_blocks(lst, obj->opt));
	while (lst)
	{
		if (S_ISLNK(lst->stat.st_mode))
			lst->name = ft_strmerge(lst->name, ls_file_readlink(lst->path));
		if ((lst && lst->name[0] == '.' && !(obj->opt & A_OPT)))
			lst = lst->next;
		else
		{
			perms = ls_file_get_permision(lst->stat.st_mode);
			perms = ls_file_get_xattr(lst->path, perms);
			t = ft_strsub(ctime((obj->opt & U_OPT) ? &lst->stat.st_atime :\
			&lst->stat.st_mtime), 4, 12);
			ft_printf("%s %2d %-9.9s %-5.5s %10llu %12.12s %-32.*s\n",\
				perms, lst->stat.st_nlink, getpwuid(lst->stat.st_uid)->pw_name,\
				getgrgid(lst->stat.st_gid)->gr_name,\
				lst->stat.st_size, t, (int)ft_strlen(lst->name), lst->name);
			free(perms);
			free(t);
			lst = lst->next;
		}
	}
}

int			ls_get_col_terminal(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

void		ls_print(t_lst_file *lst, t_ls *obj)
{
	int				c_col;
	int				i;
	int				l;
	int				c_row;
	int				j;

	l = ls_lst_name_max_length(lst);
	c_col = (obj->opt & ONE_OPT) ? 1 : (ls_get_col_terminal() / l);
	c_row = (ls_lst_length(lst, obj->opt & A_OPT) % c_col == 0) ?\
		ls_lst_length(lst, obj->opt & A_OPT) / c_col :\
		ls_lst_length(lst, obj->opt & A_OPT) / c_col + 1;
	i = -1;
	while (++i < c_row && ls_lst_length(lst, obj->opt & A_OPT))
	{
		j = -1;
		while (++j < c_col)
			if (i + j * c_row < ls_lst_length(lst, obj->opt & A_OPT))
				ft_printf("%-*.*s", l, l,\
				ls_lst_get_by_ind(lst, i + j * c_row, obj->opt & A_OPT)->name);
		ft_printf("\n");
	}
}

void		ls_print_child(t_lst_file *lst, t_ls *obj, int is_root, int count)
{
	if (is_root == 0)
		(obj->opt & L_OPT) ? ls_print_l(lst, obj) : ls_print(lst, obj);
	while (lst)
	{
		if (lst->child &&\
		(!(ls_lst_is_root(lst) && !(obj->opt & A_OPT))))
		{
			if (ft_strequ(lst->path, "ft_ls_root_slynell") != 1 &&\
			(is_root == 0 || (is_root == 1 && count > 1)))
				ft_printf("\n%s:\n", lst->path);
			if (lst->child && ft_strequ(lst->child->error, "Good") == 0)
				ft_printf("ft_ls: %s: %s\n", lst->child->name,\
				lst->child->error);
			else
				ls_print_child(lst->child, obj, ft_strequ(lst->path,\
				"ft_ls_root_slynell"), ls_lst_length(lst->child, 1));
		}
		lst = lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/09/13 09:52:11 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

void ls_print_l(t_lst_file *lst, t_ls *obj, int is_root)
{
	char *perms;
	char *t;

	while (lst)
	{
		if ((!(S_ISDIR(lst->stat.st_mode)) && is_root == 1) || is_root != 1)
		{
			if (S_ISLNK(lst->stat.st_mode))
				lst->name = ft_strmerge(lst->name, ls_file_readlink(lst->path));
			if (!(lst && lst->name[0] == '.' && !(obj->opt & A_OPT)))
			{
				perms = ls_file_get_permision(lst->stat.st_mode);
				perms = ls_file_get_xattr(lst->path, perms);
				t = ft_strsub(ctime((obj->opt & U_OPT) ? &lst->stat.st_atime : &lst->stat.st_mtime), 4, 12);
				IF_TRUE(obj->opt & S_OPT, ft_printf("%5llu ", lst->stat.st_blocks));
				ft_printf("%s %2d %-9.9s %-5.9s %9llu %12.12s %-32.*s\n",
						  perms, lst->stat.st_nlink, getpwuid(lst->stat.st_uid)->pw_name,
						  getgrgid(lst->stat.st_gid)->gr_name,
						  lst->stat.st_size, t, (int)ft_strlen(lst->name), lst->name);
				free(perms);
				free(t);
			}
		}
		lst = lst->next;
	}
}

int ls_get_col_terminal(void)
{
	struct winsize ws;

	ioctl(1, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

void ls_print(t_lst_file *lst, t_ls *obj, int i, int is_root)
{
	int c_col;
	int l;
	int c_row;
	int j;

	l = ls_lst_name_max_length(lst);
	c_col = (obj->opt & ONE_OPT) ? 1 : (ls_get_col_terminal() / l);
	c_row = (ls_lst_length(lst, is_root) % c_col == 0) ? ls_lst_length(lst, is_root) / c_col : ls_lst_length(lst, is_root) / c_col + 1;
	while (++i < c_row && ls_lst_length(lst, is_root))
	{
		j = -1;
		while (++j < c_col)
			if (i + j * c_row < ls_lst_length(lst, is_root))
			{
				IF_TRUE(obj->opt & S_OPT, ft_printf("%5llu ",
													ls_lst_get_by_ind(lst, i + j * c_row, is_root)->stat.st_blocks));
				ft_printf("%-*.*s", l, l,
						  ls_lst_get_by_ind(lst, i + j * c_row, is_root)->name);
			}
		ft_printf("\n");
	}
}

void ls_print_child(t_lst_file *lst, t_ls *obj, int is_root)
{
	(obj->opt & L_OPT) ? ls_print_l(lst, obj, is_root) : ls_print(lst, obj, -1, is_root);
	while (lst && ((is_root != 1 && obj->opt & RR_OPT) || is_root == 1))
	{
		if (S_ISDIR(lst->stat.st_mode) && ((is_root == 1 && ls_lst_is_root(lst)) || ls_lst_is_root(lst) != 1))
		{
			ft_printf("\n%s:\n", lst->path);
			if (lst->child && lst->child->error != 0)
				ft_printf("ft_ls: %s: %s\n", lst->child->name,
						  strerror(lst->child->error));
			else if (lst->child)
			{
				IF_TRUE((obj->opt & L_OPT || obj->opt & S_OPT), ft_printf("total %d\n", ls_file_get_blocks(lst->child, obj->opt)));
				ls_print_child(lst->child, obj, is_root + 1);
			}
		}
		lst = lst->next;
	}
}

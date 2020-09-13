/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/09/13 16:08:30 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

void	ls_print_l(t_lst_file *lst, int x, int is_root)
{
	char	*perms;
	char	*t;

	while (lst)
	{
		if (((!(S_ISDIR(lst->stat.st_mode)) && is_root == 1) || is_root != 1)\
	&& (!(lst && lst->name[0] == '.' && !(x & A_OPT))))
		{
			if (S_ISLNK(lst->stat.st_mode))
				lst->name = ft_strmerge(lst->name, ls_file_readlink(lst->path));
			perms = ls_xattr(lst->path, ls_perm(lst->stat.st_mode));
			t = ft_strsub(ctime((x & U_OPT) ? &lst->stat.st_atime :\
	&lst->stat.st_mtime), 4, 12);
			IF_TRUE(x & S_OPT, ft_printf("%5llu ", lst->stat.st_blocks));
			ft_printf("%s %2d %-9.9s %-5.9s %9llu %12.12s %-32.*s\n",\
	perms, lst->stat.st_nlink, (getpwuid(lst->stat.st_uid) ?\
	getpwuid(lst->stat.st_uid)->pw_name : ft_itoa(lst->stat.st_uid)),\
	getgrgid(lst->stat.st_gid)->gr_name,\
	lst->stat.st_size, t, (int)ft_strlen(lst->name), lst->name);
			free(perms);
			free(t);
		}
		lst = lst->next;
	}
}

int		ls_get_col_terminal(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

void	ls_print(t_lst_file *lst, int x, int i, int is_root)
{
	int	c_col;
	int	l;
	int	c_row;
	int	j;

	l = ls_lst_name_max_length(lst);
	c_col = (x & ONE_OPT) ? 1 : (ls_get_col_terminal() / l);
	c_row = (ls_lst_length(lst, is_root) % c_col == 0) ?\
	ls_lst_length(lst, is_root) / c_col :\
	ls_lst_length(lst, is_root) / c_col + 1;
	while (++i < c_row && ls_lst_length(lst, is_root))
	{
		j = -1;
		while (++j < c_col)
			if (i + j * c_row < ls_lst_length(lst, is_root))
			{
				IF_TRUE(x & S_OPT, ft_printf("%5llu ",\
		ls_lst_ind(lst, i + j * c_row, is_root)->stat.st_blocks));
				ft_printf("%-*.*s", l, l,\
		ls_lst_ind(lst, i + j * c_row, is_root)->name);
			}
		ft_printf("\n");
	}
}

void	ls_print_child(t_lst_file *lst, int x, int is_root, int count_dir)
{
	int	i;

	i = 0;
	(x & L_OPT) ? ls_print_l(lst, x, is_root) : ls_print(lst, x, -1, is_root);
	while (lst && ((is_root != 1 && x & RR_OPT) || is_root == 1) && ++i)
	{
		if (S_ISDIR(lst->stat.st_mode) && !(is_root == 0 && ls_root(lst)))
		{
			if (!(i == 1 && ls_lst_length(lst, 0) == 1 && is_root == 1) &&\
			!(i == 1 && count_dir == 0 && is_root == 1))
				ft_printf("\n", lst->path);
			if (!(i == 1 && ls_lst_length(lst, 0) == 1 && is_root == 1))
				ft_printf("%s:\n", lst->path);
			if (lst->child && lst->child->error != 0)
				ft_printf("ft_ls: %s: %s\n", lst->child->name,\
				strerror(lst->child->error));
			if (lst->child && lst->child->error == 0 &&\
			(x & L_OPT || x & S_OPT))
				ft_printf("total %d\n", ls_blocks(lst->child, x));
			if (lst->child && lst->child->error == 0)
				ls_print_child(lst->child, x, is_root + 1, count_dir + 1);
		}
		lst = lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_lst_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/08/17 19:21:39 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"


int ls_max_namelen(t_lst_file *lst)
{
	t_lst_file *tmp;
	int l;
	int r;

	r = 0;
	tmp = lst;
	while (tmp)
	{
		if ((l = ft_strlen(tmp->name)) > r)
			r = l;
		tmp = tmp->next;
	}
	l = r / 2;
	l += (r % 2) ? 1 : 0;
	return ((l * 2) + 1);
}

// void		ls_print_l(t_lst_file *lst, t_ls *obj)
// {
// 	char *perms;
// 	char *t;

// 	printf("total %d\n", ls_get_total_blocks(lst, obj->opt));
// 	while (lst)
// 	{
// 		if (S_ISLNK(lst->stat.st_mode))
// 			lst->name = ft_strmerge(lst->name, ft_readlink(lst->path));
// 		if (lst && lst->name[0] == '.' && !(obj->opt & A_OPT))
// 			lst = lst->next;
// 		else
// 		{
// 			perms = ls_get_perms(lst->stat.st_mode);
// 			perms = ls_check_xattr(lst->path, perms);
// 			t = ft_strsub(ctime(&lst->stat.st_mtime), (unsigned int)4, \
// 			(size_t)12);
// 			printf("%s %3d %-9.9s %-13.13s %6llu %12.12s %-32.*s\n", \
// 			perms, lst->stat.st_nlink, getpwuid(lst->stat.st_uid)->pw_name, \
// 			getgrgid(lst->stat.st_gid)->gr_name, \
// 			lst->stat.st_size, t, (int)ft_strlen(lst->name), lst->name);
// 			free(perms);
// 			free(t);
// 			lst = lst->next;
// 		}
// 	}
// }


void ls_print(t_lst_file *lst, t_ls *obj)
{
	struct winsize ws;
	int col;
	int i;
	int l;

	ioctl(1, TIOCGWINSZ, &ws);
	l = ls_max_namelen(lst);
	col = 3;
	while (lst)
	{
		i = 0;
		while (lst && lst->name && i < col)
		{
			if (lst && lst->name[0] == '.' && !(obj->opt & A_OPT))
				lst = lst->next;
			else
			{
				ft_printf("%-*.*s", l, l, lst->name);
				lst = lst->next;
				i++;
			}
		}
		ft_printf("\n");
	}
}

void ls_print_child(t_lst_file *lst, t_ls *obj)
{
	ls_print(lst, obj);
	// (obj->opt & L_OPT) ? ls_print_l(lst, obj) : ls_print(lst, obj);
	// if(lst->next)
	// {
	// 	// ls_print_child(lst->next, obj);
	// }
	while (lst)
	{
		if (lst->child && !(lst->name[0] == '.' && !(obj->opt & A_OPT)))
		{
			ft_printf("\n%s:\n", lst->path);
			lst->child = ls_lst_get_start(lst->child);
			ls_print_child(lst->child, obj);
		}
		lst = lst->next;
	}
	return;
}

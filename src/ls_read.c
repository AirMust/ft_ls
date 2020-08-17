/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/08/18 01:39:08 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

int ls_read_opt(t_ls *obj, int ac, char **av)
{
	while (obj->index < ac && *av[obj->index] == '-')
	{
		while (*(++av[obj->index]))
		{
			if (ft_str_ind("lRartu1G", *av[obj->index]) == -1)
				ls_error(av[obj->index], USAGE);
			obj->opt |= (1 << ft_str_ind("lRartu1G", *av[obj->index]));
		}
		obj->index += 1;
	}
	return (1);
}

t_lst_file *ls_read_file(char *path_dir, t_lst_file *lst, t_ls *obj)
{
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(path_dir)) == NULL)
		ls_error(path_dir, ERROR);
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
			lst = (lst) ? ls_lst_add(lst) : ls_lst_create();
			lst->name = ft_strdup(entry->d_name);
			lst->path = ls_file_concat_path_dir(path_dir, lst->name);
			if (!(lstat(lst->path, &lst->stat) == 0))
				ls_lstat_error(lst);
			if (S_ISDIR(lst->stat.st_mode) && ls_lst_is_root(lst) &&\
				obj->opt & RR_OPT)
				lst->child = ls_read_file(lst->path, lst->child, obj);
		}
		closedir(dir);
	}
	return (lst);
}

int ls_read_lst_file(t_ls *obj, int ac, char **av)
{
	t_lst_file *lst;

	ac += (av[obj->index]) ? 0 : 1;
	if (!av[obj->index])
		av[obj->index] = "./";
	while (obj->index < ac)
	{
		lst = NULL;
		if (!(lst = ls_read_file(av[obj->index], lst, obj)))
			return (1);
		if (!(lst = ls_lst_sort(lst, obj->opt)))
			return (1);
		ls_print_child(lst, obj);
		obj->index += 1;
		ls_lst_free(lst);
	}
	free(obj);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/08/17 19:23:19 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

int ls_read_opt(t_ls *obj, int ac, char **av)
{
	while (obj->index < ac && *av[obj->index] == '-')
	{
		while (*(++av[obj->index]))
		{
			if (ft_str_ind("lRart", *av[obj->index]) == -1)
				ls_error(av[obj->index], USAGE);
			obj->opt |= (1 << ft_str_ind("lRart", *av[obj->index]));
		}
		obj->index += 1;
	}
	return (1);
}


char *ls_get_file_path(char *path_dir, char *file_name)
{
	int l;
	char *temp_path;
	char *new_path;

	temp_path = NULL;
	l = ft_strlen(path_dir);
	temp_path = (path_dir[l - 1] == '/') ? ft_strdup(path_dir) : ft_strjoin(path_dir, "/");
	new_path = ft_strjoin(temp_path, file_name);
	free(temp_path);
	return (new_path);
}

t_lst_file *ls_read_file(char *path_dir, t_lst_file *lst, t_ls *obj, t_lst_file *parent)
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
			lst->parent = parent;
			lst->name = ft_strdup(entry->d_name);
			lst->path = ls_get_file_path(path_dir, lst->name);
			if (!(lstat(lst->path, &lst->stat) == 0))
				ls_lstat_error(lst);
			if (S_ISDIR(lst->stat.st_mode) && ft_strequ(lst->name, ".") == 0 && ft_strequ(lst->name, "..") == 0 &&
				obj->opt & RR_OPT)
				lst->child = ls_read_file(lst->path, lst->child, obj, lst);
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
		if (!(lst = ls_read_file(av[obj->index], lst, obj, NULL)))
			return (1);
		// printf("%s", lst->name);
		lst = ls_lst_get_start(lst);
		printf("\n");
		ls_print_child(lst, obj);

		// if (!(lst = ls_sort_files(lst, obj->opt)))
		// 	return (1);
		// if ((ac - obj->index) > 1)
		// 	printf("%s:\n", av[obj->index]);
		// else if (ft_strcmp(av[obj->index], "./") && !(is_ls_flag(av[obj->index - 1][1])) && \
		// obj->index - 1 != 0)
		// 	printf("%s:\n", av[obj->index]);
		// ls_print_files(lst, obj->opt);
		// if ((ac - obj->index) > 1)
		// 	printf("\n");
		obj->index += 1;
		ls_lst_free(lst);
	}
	return (0);
}

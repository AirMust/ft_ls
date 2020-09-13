/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/09/13 09:52:05 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

int ls_read_opt(t_ls *obj, int ac, char **av)
{
	while (obj->index < ac && *av[obj->index] == '-')
	{
		if (ft_strequ(av[obj->index], "-"))
			return (1);
		if (ft_strequ(av[obj->index], "--"))
		{
			obj->index += 1;
			return (1);
		}
		while (*(++av[obj->index]))
		{
			if (ft_str_ind("lRartu1sc", *av[obj->index]) == -1)
				ls_error(av[obj->index], USAGE);
			obj->opt |= (1 << ft_str_ind("lRartu1sc", *av[obj->index]));
		}
		obj->index += 1;
	}
	return (1);
}

t_lst_file *pre_error(char *path_dir, char *name, t_lst_file *lst)
{
	ls_lst_free(lst);
	lst = ls_lst_create(0);
	if (name)
		lst->name = ft_strdup(name);
	else
		lst->name = ft_strdup(path_dir);
	if (path_dir)
		lst->path = ft_strdup(path_dir);
	if (errno == 20)
		if (!(lstat(lst->path, &lst->stat) == 0))
			return (pre_error(path_dir, name, lst));
	lst->child = NULL;
	lst->error = errno;
	if (errno != 13 && errno != 20)
	{
		ls_error(path_dir, ERROR);
		ls_lst_free(lst);
		return (NULL);
	}
	return (lst);
}

t_lst_file *ls_read_file(char *path_dir, char *name,
						 t_lst_file *lst, t_ls *x)
{
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(path_dir)) == NULL)
		lst = pre_error(path_dir, name, lst);
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if ((entry->d_name[0] == '.' && x->opt & A_OPT) || entry->d_name[0] != '.')
			{
				lst = (lst) ? ls_lst_add(lst) : ls_lst_create(0);
				lst->name = ft_strdup(entry->d_name);
				lst->path = ls_file_concat_path_dir(path_dir, lst->name);
				lst->error = 0;
				if (!(lstat(lst->path, &lst->stat) == 0))
					lst = pre_error(path_dir, name, lst);
				if (S_ISDIR(lst->stat.st_mode) && !ls_lst_is_root(lst) &&
					x->opt & RR_OPT)
					lst->child = ls_read_file(lst->path, lst->name, lst->child, x);
			}
		}
		closedir(dir);
	}

	return (lst);
}

int ls_read_lst_file(t_ls *obj, int ac, char **av)
{
	t_lst_file *lst;
	t_lst_file *root;
	t_lst_file *main;
	int s;

	s = 0;
	main = ls_lst_create(1);
	root = main;
	ac += (av[obj->index]) ? 0 : 1;
	if (!av[obj->index])
		av[obj->index] = ft_strdup(".");
	while (obj->index < ac)
	{
		lst = NULL;
		obj->index += 1;

		lst = (lst) ? ls_lst_add(lst) : ls_lst_create(0);
		lst->name = ft_strdup(av[obj->index - 1]);
		lst->path = ft_strdup(av[obj->index - 1]);
		lst->error = 0;
		if (!(lstat(lst->path, &lst->stat) == 0))
			lst = pre_error(av[obj->index - 1], NULL, lst);

		if (lst)
		{
			if(S_ISDIR(lst->stat.st_mode))
				lst->child = ls_read_file(lst->name, NULL, NULL, obj);
			if ((s++) == 0)
			{
				root->child = lst;
				root = root->child;
			}
			else
			{
				lst->prev = root;
				root->next = lst;
				root = root->next;
			}
		}

	}
	main = ls_lst_sort(main, obj->opt);
	ls_print_child(main->child, obj, 1);
//
	// ls_lst_print_lst(main, 0);

	// main = ls_lst_sort(main, obj->opt);
	ls_lst_free(main);
	free(obj);
	return (0);
}

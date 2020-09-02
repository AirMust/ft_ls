/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/09/03 00:58:19 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

int			ls_read_opt(t_ls *obj, int ac, char **av)
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

t_lst_file	*pre_error(char *path_dir, char *name, t_lst_file *lst)
{
	ls_lst_free(lst);
	if (errno == 13)
	{
		lst = ls_lst_create(0);
		lst->name = ft_strdup(name);
		lst->path = ft_strdup(path_dir);
		lst->error = ft_strdup(strerror(errno));
	}
	else
		ls_error(path_dir, ERROR);
	return (lst);
}

t_lst_file	*ls_read_file(char *path_dir, char *name,\
			t_lst_file *lst, t_ls *x)
{
	DIR				*dir;
	struct dirent	*entry;

	if ((dir = opendir(path_dir)) == NULL)
		lst = pre_error(path_dir, name, lst);
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
			lst = (lst) ? ls_lst_add(lst) : ls_lst_create(0);
			lst->name = ft_strdup(entry->d_name);
			lst->path = ls_file_concat_path_dir(path_dir, lst->name);
			lst->error = ft_strdup("Good");
			if (!(lstat(lst->path, &lst->stat) == 0))
				lst = pre_error(path_dir, name, lst);
			if (S_ISDIR(lst->stat.st_mode) && !ls_lst_is_root(lst) &&
			x->opt & RR_OPT && !(lst->name[0] == '.' && !(x->opt & A_OPT)))
				lst->child = ls_read_file(lst->path, lst->name, lst->child, x);
		}
		closedir(dir);
	}
	return (lst);
}

int			ls_read_lst_file(t_ls *obj, int ac, char **av)
{
	t_lst_file	*lst;
	t_lst_file	*root;
	t_lst_file	*main;
	int			s;

	s = 0;
	main = ls_lst_create(1);
	root = main;
	ac += (av[obj->index]) ? 0 : 1;
	if (!av[obj->index])
		av[obj->index] = ft_strdup("./");
	while (obj->index < ac)
	{
		lst = NULL;
		obj->index += 1;
		lst = ls_read_file(av[obj->index - 1], NULL, lst, obj);
		root = ls_lst_insert(root, lst, (s++) == 0, av[obj->index - 1]);
	}
	main = ls_lst_sort(main, obj->opt);
	// ls_lst_print_lst(main, 0);
	ls_print_child(main, obj, 1, 1);
	ls_lst_free(main);
	free(obj);
	return (0);
}

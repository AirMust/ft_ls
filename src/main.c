#include "../header/ft_ls.h"

int get_ls_option(t_ls *obj, int ac, char **av)
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

char *ls_get_path(char *path_dir, char *file_name)
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

t_lst_file *ls_init_file(char *path_dir, t_lst_file *lst, t_ls *obj, t_lst_file *parent)
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
			lst->path = ls_get_path(path_dir, lst->name);
			if (!(lstat(lst->path, &lst->stat) == 0))
				ls_lstat_error(lst);
			if (S_ISDIR(lst->stat.st_mode) && ft_strequ(lst->name, ".") == 0 && ft_strequ(lst->name, "..") == 0 &&
				obj->opt & RR_OPT)
				lst->child = ls_init_file(lst->path, lst->child, obj, lst);
		}
		closedir(dir);
	}
	return (lst);
}
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

void		ls_print_l(t_lst_file *lst, t_ls *obj)
{
	char *perms;
	char *t;

	printf("total %d\n", ls_get_total_blocks(lst, obj->opt));
	while (lst)
	{
		if (S_ISLNK(lst->stat.st_mode))
			lst->name = ft_strmerge(lst->name, ft_readlink(lst->path));
		if (lst && lst->name[0] == '.' && !(obj->opt & A_OPT))
			lst = lst->next;
		else
		{
			perms = ls_get_perms(lst->stat.st_mode);
			perms = ls_check_xattr(lst->path, perms);
			t = ft_strsub(ctime(&lst->stat.st_mtime), (unsigned int)4, \
			(size_t)12);
			printf("%s %3d %-9.9s %-13.13s %6llu %12.12s %-32.*s\n", \
			perms, lst->stat.st_nlink, getpwuid(lst->stat.st_uid)->pw_name, \
			getgrgid(lst->stat.st_gid)->gr_name, \
			lst->stat.st_size, t, (int)ft_strlen(lst->name), lst->name);
			free(perms);
			free(t);
			lst = lst->next;
		}
	}
}


void ls_print(t_lst_file *lst, t_ls *obj)
{
	struct winsize ws;
	int col;
	int i;
	int l;

	ioctl(1, TIOCGWINSZ, &ws);
	l = ls_max_namelen(lst);
	col = ws.ws_col / l;
	// col = (*obj->opt & ONE_FLAG) ? 1 : (ws.ws_col / l);
	while (lst)
	{
		i = 0;
		while (lst && lst->name && i < col)
		{
			if (lst && lst->name[0] == '.' && !(obj->opt & A_OPT))
				lst = lst->next;
			else
			{
				printf("%-*.*s", l, l, lst->name);
				lst = lst->next;
				i++;
			}
		}
		printf("\n");
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
			printf("\n%s:\n", lst->path);
			lst->child = ls_lst_get_start(lst->child);
			ls_print_child(lst->child, obj);
		}
		lst = lst->next;
	}
	return;
}

// void ls_print(t_lst_file *lst)
// {
// 	printf("")
// 	if(lst->child)
// }

int ls_init(t_ls *obj, int ac, char **av)
{
	t_lst_file *lst;

	ac += (av[obj->index]) ? 0 : 1;
	if (!av[obj->index])
		av[obj->index] = "./";
	while (obj->index < ac)
	{
		lst = NULL;
		if (!(lst = ls_init_file(av[obj->index], lst, obj, NULL)))
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

int main(int ac, char **av)
{
	t_ls *obj;

	obj = (t_ls *)(malloc(sizeof(t_ls)));
	obj->index = 1;
	obj->opt = 0;
	if (get_ls_option(obj, ac, av) == 0)
		return (1);
	return (ls_init(obj, ac, av));
}

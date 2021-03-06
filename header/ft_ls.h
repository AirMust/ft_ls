/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/09/13 16:10:19 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdint.h>
# include <limits.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <uuid/uuid.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include "../libft/header/libft.h"

# define L_OPT 		1
# define RR_OPT 	2
# define A_OPT 		4
# define R_OPT 		8
# define T_OPT 		16
# define U_OPT 		32
# define ONE_OPT	64
# define S_OPT		128
# define C_OPT		256

enum					{ERROR, USAGE};

typedef struct			s_ls {
	int					opt;
	int					index;
}						t_ls;

typedef struct			s_lst_file {
	struct s_lst_file	*child;
	struct s_lst_file	*prev;
	struct s_lst_file	*next;
	char				*path;
	char				*name;
	int					error;
	struct stat			stat;
}						t_lst_file;

/*
** ========================== LS FUNCTION ===================================
*/
int						ls_read_opt(t_ls *obj, int ac, char **av);
int						ls_read_lst_file(t_ls *obj, int ac, char **av);
t_lst_file				*ls_read_f(char *path_dir, char *name,\
						t_lst_file *lst, int x);
void					ls_print_child(t_lst_file *lst, int x,\
						int is_root, int count);
/*
** ========================== ERROR FUNCTION ===================================
*/
int						ls_error(char *s, int error);

/*
** ========================== FUNCTION LIST FILES ==============================
*/
t_lst_file				*ls_lst_create(int is_root);
t_lst_file				*ls_lst_add(t_lst_file *lst);
t_lst_file				*ls_lst_insert(t_lst_file *root,\
						t_lst_file *lst, int *s, int x);
t_lst_file				*ls_lst_get_start(t_lst_file *lst);
t_lst_file				*ls_lst_reverse(t_lst_file *lst);
void					ls_lst_free(t_lst_file *lst);
t_lst_file				*ls_lst_swap(t_lst_file *lst);
int						ls_lst_length(t_lst_file *lst, int is_hidden);
int						ls_lst_sort_by_atime(t_lst_file *lst);
int						ls_lst_sort_by_ctime(t_lst_file *lst);
int						ls_lst_sort_by_mtime(t_lst_file *lst);
int						ls_lst_sort_by_name(t_lst_file *lst);
int						ls_root(t_lst_file *lst);
t_lst_file				*ls_lst_sort(t_lst_file *lst, int opt);
void					ls_lst_print_lst(t_lst_file *lst, int depth);
t_lst_file				*ls_lst_ind(t_lst_file *lst, int index,\
						int is_hidden);
size_t					ls_lst_name_max_length(t_lst_file *lst);

/*
** ========================== FUNCTION FILES ==============================
*/
char					*ls_file_concat_path_dir(char *path_dir,\
						char *file_name);
char					ls_file_get_type(mode_t st_mode);
char					*ls_perm(mode_t st_mode);
int						ls_blocks(t_lst_file *file, int opt);
char					*ls_file_readlink(char *path);
char					*ls_xattr(char *path, char *perms);

#endif

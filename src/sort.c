/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/17 19:27:26 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

t_lst_file		*ls_sort_time(t_lst_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && \
	lst->stat.st_mtimespec.tv_sec < lst->next->stat.st_mtimespec.tv_sec)
		lst = ls_swap_files(lst);
	else if (lst->next && \
	lst->stat.st_mtimespec.tv_sec == lst->next->stat.st_mtimespec.tv_sec)
	{
		if (lst->next && \
		lst->stat.st_mtimespec.tv_nsec < lst->next->stat.st_mtimespec.tv_nsec)
			lst = ls_swap_files(lst);
	}
	lst->next = ls_sort_time(lst->next);
	return (lst);
}

t_lst_file		*ls_sort_alpha(t_lst_file *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		lst = ls_swap_files(lst);
	lst->next = ls_sort_alpha(lst->next);
	return (lst);
}

t_lst_file		*ls_sort_bubble(t_lst_file *lst, int *flags)
{
	int c;
	int i;

	i = 0;
	c = ls_file_count(lst);
	while (i < c)
	{
		if (*flags & T_FLAG)
			lst = ls_sort_time(lst);
		else
			lst = ls_sort_alpha(lst);
		i++;
	}
	if (*flags & R_FLAG)
		lst = ls_reverse_files(lst);
	return (lst);
}

t_lst_file		*ls_sort_files(t_lst_file *lst, int *flags)
{
	t_lst_file *tmp;

	lst = ls_goto_first_file(lst);
	lst = ls_sort_bubble(lst, flags);
	tmp = lst;
	while (tmp)
	{
		if (tmp->child && !is_ls_hidden(tmp->name))
			tmp->child = ls_sort_files(tmp->child, flags);
		tmp = tmp->next;
	}
	return (lst);
}

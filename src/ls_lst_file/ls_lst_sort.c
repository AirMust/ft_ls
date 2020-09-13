/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 15:11:51 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file	*ls_lst_sort_by(t_lst_file *lst, int (*sort_by)(t_lst_file *))
{
	if (!lst)
		return (NULL);
	if (sort_by(lst))
		lst = ls_lst_swap(lst);
	lst->next = ls_lst_sort_by(lst->next, sort_by);
	return (lst);
}

t_lst_file	*ls_lst_map_sort(t_lst_file *lst, int opt)
{
	int i;

	i = -1;
	while (++i < ls_lst_length(lst, 2))
	{
		if (opt & T_OPT && opt & C_OPT)
			lst = ls_lst_sort_by(lst, &ls_lst_sort_by_ctime);
		if (opt & T_OPT && opt & U_OPT)
			lst = ls_lst_sort_by(lst, &ls_lst_sort_by_atime);
		else if (opt & T_OPT)
			lst = ls_lst_sort_by(lst, &ls_lst_sort_by_mtime);
		else
			lst = ls_lst_sort_by(lst, &ls_lst_sort_by_name);
	}
	if (opt & R_OPT)
		lst = ls_lst_reverse(lst);
	return (lst);
}

t_lst_file	*ls_lst_sort(t_lst_file *lst, int opt)
{
	t_lst_file *temp_lst;

	lst = ls_lst_get_start(lst);
	lst = ls_lst_map_sort(lst, opt);
	temp_lst = lst;
	while (temp_lst)
	{
		if (temp_lst->child)
			temp_lst->child = ls_lst_sort(temp_lst->child, opt);
		temp_lst = temp_lst->next;
	}
	return (lst);
}

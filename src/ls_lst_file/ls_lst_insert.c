/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 15:23:34 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_insert(t_lst_file *root, t_lst_file *lst,\
				int *s, int x)
{
	if (lst)
	{
		if (S_ISDIR(lst->stat.st_mode))
			lst->child = ls_read_f(lst->name, NULL, NULL, x);
		if ((*s)++ == 0)
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
	return (root);
}

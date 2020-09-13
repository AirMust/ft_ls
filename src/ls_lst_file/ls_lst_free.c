/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 12:34:49 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

void	ls_lst_free(t_lst_file *lst)
{
	t_lst_file *temp_lst;

	if (lst)
	{
		if (lst->prev)
			lst = ls_lst_get_start(lst);
		while (lst)
		{
			temp_lst = lst->next;
			free(lst->path);
			free(lst->name);
			if (lst->child)
				ls_lst_free(lst->child);
			free(lst);
			lst = temp_lst;
		}
		lst = NULL;
	}
}

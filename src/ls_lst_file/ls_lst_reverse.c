/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/17 18:42:58 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_reverse(t_lst_file *lst)
{
	t_lst_file *temp_lst;

	while (lst)
	{
		temp_lst = lst->next;
		lst->next = lst->prev;
		lst->prev = temp_lst;
		if (lst->prev)
			lst = lst->prev;
		else
			return (lst);
	}
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/17 19:27:57 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_swap(t_lst_file *lst)
{
	t_lst_file *temp_lst;

	temp_lst = lst->next;
	lst->next = temp_lst->next;
	temp_lst->prev = lst->prev;
	lst->prev = temp_lst;
	temp_lst->next = lst;
	if (lst->next)
		lst->next->prev = lst;
	if (temp_lst->prev)
		temp_lst->prev->next = temp_lst;
	lst = lst->prev;
	return (lst);
}

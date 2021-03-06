/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/01 18:57:56 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_add(t_lst_file *lst)
{
	t_lst_file	*temp_lst;

	temp_lst = ls_lst_create(0);
	temp_lst->next = lst;
	lst->prev = temp_lst;
	lst = lst->prev;
	return (lst);
}

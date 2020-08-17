/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/17 18:41:44 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_create(void)
{
	t_lst_file	*lst;

	if (!(lst = (t_lst_file *)malloc(sizeof(t_lst_file))))
		ls_error("", ERROR);
	lst->prev = NULL;
	lst->parent = NULL;
	lst->child = NULL;
	lst->path = NULL;
	lst->name = NULL;
	lst->next = NULL;
	return (lst);
}

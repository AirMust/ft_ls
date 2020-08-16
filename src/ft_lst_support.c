/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/16 23:58:41 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

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

t_lst_file		*ls_lst_add(t_lst_file *lst)
{
	t_lst_file	*temp_lst;

	temp_lst = ls_lst_create();
	temp_lst->prev = lst;
	lst->next = temp_lst;
	lst = lst->next;
	return (lst);
}

t_lst_file		*ls_lst_get_start(t_lst_file *lst)
{
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

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

void		ls_lst_free(t_lst_file *lst)
{
	t_lst_file *temp_lst;

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

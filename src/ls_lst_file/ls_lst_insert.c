/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/27 02:07:43 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_insert(t_lst_file *lst, t_lst_file *child, int is_new, char *path)
{
	t_lst_file	*temp;

	temp = ls_lst_create();
	temp->name = ft_strdup(path);
	temp->path = ft_strdup(path);
	temp->error = ft_strdup("Good");
	temp->child = child;
	if(is_new)
	{
		lst->child = temp;
		lst = lst->child;
	}
	else
	{
		temp->prev = lst;
		lst->next = temp;
		lst = lst->next;
	}
	return (lst);
}
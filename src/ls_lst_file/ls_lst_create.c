/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/12 00:39:21 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file		*ls_lst_create(int is_root)
{
	t_lst_file	*lst;

	if (!(lst = (t_lst_file *)malloc(sizeof(t_lst_file))))
		ls_error("", ERROR);
	lst->prev = NULL;
	lst->child = NULL;
	lst->path = NULL;
	lst->name = NULL;
	lst->next = NULL;
	lst->error = 0;
	if (is_root)
	{
		lst->name = ft_strdup("ft_ls_root_slynell");
		lst->path = ft_strdup("ft_ls_root_slynell");
	}
	return (lst);
}

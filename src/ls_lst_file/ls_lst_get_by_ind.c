/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_get_by_ind.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/30 18:52:39 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file	*ls_lst_get_by_ind(t_lst_file *lst, int index, int is_hidden)
{
	t_lst_file	*temp;
	int			i;

	i = -1;
	temp = lst;
	while (temp->next && i != index)
	{
		if (!(temp && temp->name[0] == '.' && !is_hidden))
			i++;
		if (i == index)
			break ;
		temp = temp->next;
	}
	return (temp);
}

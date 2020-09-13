/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_get_by_ind.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 09:51:50 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file	*ls_lst_get_by_ind(t_lst_file *lst, int index, int is_root)
{
	t_lst_file	*temp;
	int			i;

	i = -1;
	temp = lst;
	while (temp->next && i != index)
	{
		if(((is_root == 1 && !(S_ISDIR(temp->stat.st_mode))) || is_root != 1))
		// if (!((!(S_ISDIR(lst->stat.st_mode)) && is_root == 1) || is_root != 1))
			i++;
		if (i == index)
			break ;
		temp = temp->next;
	}
	return (temp);
}

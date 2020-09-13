/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_ind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 15:32:15 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

t_lst_file	*ls_lst_ind(t_lst_file *lst, int index, int is_root)
{
	t_lst_file	*temp;
	int			i;

	i = -1;
	temp = lst;
	while (temp->next && i != index)
	{
		if (((is_root == 1 && !(S_ISDIR(temp->stat.st_mode)))\
			|| is_root != 1))
			i++;
		if (i == index)
			break ;
		temp = temp->next;
	}
	return (temp);
}

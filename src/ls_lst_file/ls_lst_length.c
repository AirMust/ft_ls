/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 14:41:00 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

int			ls_lst_length(t_lst_file *lst, int is_root)
{
	t_lst_file	*temp_lst;
	int			c;

	c = 0;
	temp_lst = lst;
	while (temp_lst)
	{
		if ((is_root == 1 && !(S_ISDIR(temp_lst->stat.st_mode)))\
		|| is_root != 1)
			c++;
		temp_lst = temp_lst->next;
	}
	return (c);
}

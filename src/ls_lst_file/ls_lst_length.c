/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/01 17:48:28 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

int			ls_lst_length(t_lst_file *lst, int is_hidden)
{
	t_lst_file	*temp_lst;
	int			c;

	c = 0;
	temp_lst = lst;
	while (temp_lst->next)
	{
		if (!(temp_lst && temp_lst->name[0] == '.' && !is_hidden))
			c++;
		temp_lst = temp_lst->next;
	}
	return (c);
}

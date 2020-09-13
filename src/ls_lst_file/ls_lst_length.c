/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/13 09:51:39 by air_must         ###   ########.fr       */
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
		if ((is_root == 1 && !(S_ISDIR(temp_lst->stat.st_mode))) || is_root != 1)
		// if (!(temp_lst && temp_lst->name[0] == '.' && temp_lst->name[1] != '/' && !is_hidden))
			c++;
		temp_lst = temp_lst->next;
	}
	return (c);
}

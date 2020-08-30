/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 05:17:48 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/30 17:46:36 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

int			ls_lst_length(t_lst_file *lst, int is_hidden)
{
	t_lst_file	*temp_lst;
	int			c;

	c = 1;
	temp_lst = lst;
	while (temp_lst->next)
	{
		if (!(temp_lst && temp_lst->name[0] == '.' && !is_hidden))
			c++;
		temp_lst = temp_lst->next;
	}
	return (c);
}

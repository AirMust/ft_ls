/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_print_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/30 18:51:51 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

void	ls_lst_print_lst(t_lst_file *lst, int depth)
{
	t_lst_file	*temp;
	int			i;

	temp = lst;
	while (temp)
	{
		i = -1;
		while (++i < depth)
		{
			ft_printf("\t");
		}
		ft_printf("%s\n", temp->path);
		if (temp->child)
			ls_lst_print_lst(temp->child, depth + 1);
		temp = temp->next;
	}
	return ;
}

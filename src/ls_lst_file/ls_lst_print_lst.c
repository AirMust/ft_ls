/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_print_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/27 01:55:38 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

void	ls_lst_print_lst(t_lst_file *lst, int depth)
{
	t_lst_file *temp;
	int i;
	temp = lst;
	while(temp)
	{
		i = -1;
		while(++i < depth)
		{
			printf("\t");
		}
		printf("%s\n", temp->path);
		if(temp->child)
			ls_lst_print_lst(temp->child, depth + 1);

		temp = temp->next;
	}
	return ;
}
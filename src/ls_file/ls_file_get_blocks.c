/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_get_blocks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 04:24:15 by havi              #+#    #+#             */
/*   Updated: 2020/08/30 18:54:25 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

int				ls_file_get_blocks(t_lst_file *file, int opt)
{
	t_lst_file	*temp_lst;
	int			blocks;

	temp_lst = file;
	blocks = 0;
	while (temp_lst)
	{
		if ((opt & A_OPT) == 0 && temp_lst->name[0] != '.')
			blocks += temp_lst->stat.st_blocks;
		else if (opt & A_OPT)
			blocks += temp_lst->stat.st_blocks;
		temp_lst = temp_lst->next;
	}
	return (blocks);
}

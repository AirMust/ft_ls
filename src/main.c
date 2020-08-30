/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 18:55:04 by slynell           #+#    #+#             */
/*   Updated: 2020/08/30 18:55:18 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

int		main(int ac, char **av)
{
	t_ls	*obj;

	obj = (t_ls *)(malloc(sizeof(t_ls)));
	obj->index = 1;
	obj->opt = 0;
	if (ls_read_opt(obj, ac, av) == 0)
		return (1);
	return (ls_read_lst_file(obj, ac, av));
}

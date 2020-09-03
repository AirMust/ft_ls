/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 02:06:07 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/03 20:08:08 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

void			ls_lstat_error(t_lst_file *lst)
{
	ls_lst_free(lst);
	ft_printf("%s %d", lst->name, errno);
	exit(EXIT_FAILURE);
}

int				ls_error(char *s, int error)
{
	if (error == USAGE)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*s, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage: ft_ls [-alRrtu1sc] [file ...]", 2);
		exit(EXIT_FAILURE);
	}
	else if (error == ERROR)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (0);
}

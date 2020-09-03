/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_sort_by_ctime.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/09/03 20:07:51 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

int				ls_lst_sort_by_ctime(t_lst_file *lst)
{
	if (lst->next &&\
	lst->stat.st_ctimespec.tv_sec < lst->next->stat.st_ctimespec.tv_sec)
		return (1);
	else if (lst->next &&\
	lst->stat.st_ctimespec.tv_sec == lst->next->stat.st_ctimespec.tv_sec &&\
	lst->stat.st_ctimespec.tv_nsec < lst->next->stat.st_ctimespec.tv_nsec)
		return (1);
	else if (lst->next &&\
	lst->stat.st_ctimespec.tv_sec == lst->next->stat.st_ctimespec.tv_sec &&\
	lst->stat.st_ctimespec.tv_nsec == lst->next->stat.st_ctimespec.tv_nsec &&\
	ls_lst_sort_by_name(lst))
		return (1);
	return (0);
}

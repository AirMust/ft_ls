/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lst_sort_by_atime.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:02:27 by hbhuiyan          #+#    #+#             */
/*   Updated: 2020/08/30 18:47:58 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

int				ls_lst_sort_by_atime(t_lst_file *lst)
{
	if (lst->next && \
	lst->stat.st_atimespec.tv_sec < lst->next->stat.st_atimespec.tv_sec)
		return (1);
	else if (lst->next && \
	lst->stat.st_atimespec.tv_sec == lst->next->stat.st_atimespec.tv_sec &&\
	lst->stat.st_atimespec.tv_nsec < lst->next->stat.st_atimespec.tv_nsec)
		return (1);
	return (0);
}

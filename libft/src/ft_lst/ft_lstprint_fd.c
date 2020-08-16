/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:42:23 by slynell           #+#    #+#             */
/*   Updated: 2019/09/17 19:42:26 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstprint_fd(t_list *alst, int fd)
{
	while (alst)
	{
		ft_putstr_fd((char*)alst->content, fd);
		alst = alst->next;
	}
	ft_putstr_fd("\n", fd);
}

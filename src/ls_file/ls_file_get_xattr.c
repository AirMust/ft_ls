/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_get_xattr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 04:24:15 by havi              #+#    #+#             */
/*   Updated: 2020/08/18 00:52:41 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_ls.h"

char		*ls_file_get_xattr(char *path, char *perms)
{
	char *tmp;

	tmp = perms;
	perms = listxattr(path, 0, 0, XATTR_NOFOLLOW) > 0 ? \
	ft_strjoin(tmp, "@") : ft_strjoin(tmp, " ");
	free(tmp);
	return (perms);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_get_xattr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 04:24:15 by havi              #+#    #+#             */
/*   Updated: 2020/08/30 18:53:11 by slynell          ###   ########.fr       */
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

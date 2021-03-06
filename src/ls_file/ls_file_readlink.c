/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_readlink.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 02:56:05 by havi              #+#    #+#             */
/*   Updated: 2020/09/13 14:11:51 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

char		*ls_file_readlink(char *path)
{
	char	buf[128];
	ssize_t	len;
	ssize_t	buffsize;

	buffsize = 128;
	buf[0] = ' ';
	buf[1] = '-';
	buf[2] = '>';
	buf[3] = ' ';
	if (!(len = readlink(path, &buf[4], (buffsize - 4))))
		exit(EXIT_FAILURE);
	buf[len + 4] = '\0';
	return (ft_strdup(buf));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_get_permision.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: air_must <air_must@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/08/18 00:02:03 by air_must         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

char		*ls_file_get_permision(mode_t st_mode)
{
	char	*temp;

	temp = ft_strnew(11);
	temp[0] = ls_file_get_type(st_mode);
	temp[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	temp[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	temp[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	temp[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	temp[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	temp[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	temp[7] = (st_mode & S_IROTH) ? 'r' : '-';
	temp[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	temp[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	temp[10] = 0;
	if (st_mode & S_ISUID)
		temp[3] = (st_mode & S_IXUSR) ? 's' : 'S';
	if (st_mode & S_ISGID)
		temp[6] = (st_mode & S_IXGRP) ? 's' : 'S';
	if (st_mode & S_ISVTX)
		temp[9] = (st_mode & S_IXOTH) ? 't' : 'T';
	return (temp);
}

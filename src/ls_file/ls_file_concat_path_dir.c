/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_concat_path_dir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 14:22:06 by slynell           #+#    #+#             */
/*   Updated: 2020/08/30 18:54:34 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_ls.h"

char	*ls_file_concat_path_dir(char *path_dir, char *file_name)
{
	int		l;
	char	*temp_path;
	char	*new_path;

	temp_path = NULL;
	l = ft_strlen(path_dir);
	temp_path = (path_dir[l - 1] == '/') ? ft_strdup(path_dir)\
				: ft_strjoin(path_dir, "/");
	new_path = ft_strjoin(temp_path, file_name);
	free(temp_path);
	return (new_path);
}

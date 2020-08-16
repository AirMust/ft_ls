/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynell <slynell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 13:52:59 by slynell           #+#    #+#             */
/*   Updated: 2020/07/25 13:53:06 by slynell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_array_max(int *array, int len)
{
	int	i;
	int	max;

	max = INT32_MIN;
	i = -1;
	while (++i < len)
		if (max < array[i])
			max = array[i];
	return (max);
}

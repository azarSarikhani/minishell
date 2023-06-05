/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:36:50 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/11 16:22:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init_arr(t_arr **arr, size_t len, size_t size)
{
	if (!arr || !(*arr) || size <= 0)
		return (-1);
	(*arr)->n_alloc = len * size;
	(*arr)->len = 0;
	(*arr)->size = size;
	if (len == 0)
		(*arr)->start = NULL;
	else
	{
		(*arr)->start = malloc((*arr)->n_alloc);
		if (!(*arr)->start)
			return (-1);
	}
	return (1);
}

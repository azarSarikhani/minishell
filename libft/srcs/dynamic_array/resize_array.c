/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:36:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/18 15:55:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//something's wrong here

int	resize_arr(t_arr **arr, size_t target_len)
{
	t_arr	*dst;

	if (!arr)
		return (-1);
	else if (!(*arr)->start)
		return (init_arr(arr, target_len, (*arr)->size));
	else if (init_arr(&dst, target_len, (*arr)->size) < 0)
		return (-1);
	ft_memcpy(dst->start, (*arr)->start, (*arr)->len * (*arr)->size);
	dst->len = (*arr)->len;
	reset_arr(*arr);
	arr = &dst;
	return (1);
}

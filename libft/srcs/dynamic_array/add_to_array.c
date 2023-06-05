/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:18:41 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/18 15:31:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	add_to_arr(t_arr **arr, void *elem)
{
	if (!arr || (!*arr) || !elem)
		return (-1);
	else if (!(*arr)->start)
		init_arr(arr, 1, (*arr)->size);
	ft_printf("hello from adding\n");
	if ((*arr)->size * (*arr)->len >= (*arr)->n_alloc)
		if (resize_arr(arr, (*arr)->len * 2) < 0)
			return (-1);
	ft_memcpy(&(*arr)->start[(*arr)->size * (*arr)->len], elem, (*arr)->size);
	(*arr)->len++;
	return (1);
}

int	append_array(t_arr *dst, t_arr *add)
{
	int		ret;
	size_t	n_alloc;

	if (!dst || !add || !add->start)
		return (-1);
	else if (!dst->start)
		init_arr(&dst, 1, dst->size);
	n_alloc = dst->len * dst->size + add->len * add->size;
	if (dst->n_alloc < n_alloc)
	{
		if (dst->n_alloc * 2 < dst->len * n_alloc)
			ret = resize_arr(&dst, n_alloc);
		else
			ret = resize_arr(&dst, dst->n_alloc * 2);
		if (ret < 0)
			return (-1);
	}
	ft_memcpy(&dst->start[dst->size * dst->len], add->start,
		add->len * add->size);
	dst->len += add->len;
	return (1);
}

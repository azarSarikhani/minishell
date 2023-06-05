/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:29:07 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/18 13:45:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*get_elem_arr(t_arr *arr, size_t index)
{
	unsigned char	*ptr;

	if (index >= arr->len || !arr || !arr->start)
		return (NULL);
	ptr = &arr->start[arr->size * index];
	return (ptr);
}

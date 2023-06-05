/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:36:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/11 12:33:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	reset_arr(t_arr *arr)
{
	if (!arr || arr->n_alloc == 0)
		return ;
	ft_free(arr->start);
	arr->start = NULL;
	arr->n_alloc = 0;
	arr->size = 0;
	arr->len = 0;
}

void	free_arr(t_arr *arr)
{
	if (!arr || arr->n_alloc == 0)
		return ;
	ft_free(arr->start);
	arr->start = NULL;
	arr->n_alloc = 0;
	arr->size = 0;
	arr->len = 0;
	ft_free(arr);
}

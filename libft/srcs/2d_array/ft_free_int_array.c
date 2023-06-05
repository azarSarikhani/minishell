/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:38:50 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 17:09:09 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_int_array(int ***array, size_t n_elems)
{
	size_t	i;

	i = 0;
	while (i < n_elems)
		free((*array)[i++]);
	free(*array);
	*array = NULL;
}

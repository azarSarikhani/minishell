/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:29:25 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 15:38:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_matrix(int **row_array, size_t row, size_t col)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < row)
	{
		j = 0;
		while (j < col)
			ft_printf("%d ", row_array[i][j++]);
		ft_printf("\n");
	}
}

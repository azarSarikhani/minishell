/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:50:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/08 15:43:30 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <string.h>
#include "ft_error.h"

void	ft_error(int error, char *str)
{	
	if (error == 0)
		exit(1);
	if (error == NOFILE)
		ft_printf_fd(STDERR_FILENO, "pipex: no such file or directory: %s\n",
			str);
	else if (error == NOACCESS)
		ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", strerror(EACCES), str);
	else
	{
		if (error == EACCES)
			ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n",
				strerror(error), str);
		else if (error == NOCMMD)
			ft_printf_fd(STDERR_FILENO, "pipex: command not found: %s\n", str);
		exit(error);
	}
}
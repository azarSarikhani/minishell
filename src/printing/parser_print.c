/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:07:32 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 16:36:55 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#define N_PARAMS 5

void	print_parser(t_command *command)
{
	if (!command)
	{
		ft_printf("END\n");
		return ;
	}
	ft_printf("command: %s\n", command->command);
	ft_printf("ID: %d\n", command->id);
	ft_printf("-----------------------\n");
	ft_printf("PARAMS:\n");
	ft_print_array(command->params, STDOUT_FILENO);
	ft_printf("n_params: %d\n", command->n_params);
	ft_printf("-----------------------\n");
	ft_printf("infile:\t%s\n", command->infile);
	ft_printf("infile fd:\t%d\n", command->fds[0]);
	ft_printf("redirect:\t%d\n", command->in_redirect);
	ft_printf("-----------------------\n");
	ft_printf("outfile:\t%s\n", command->outfile);
	ft_printf("outfile fd:\t%d\n", command->fds[1]);
	ft_printf("redirect:\t%d\n", command->out_redirect);
	ft_printf("=======================\n");
	print_parser(command->next);
}

// int	main(void)
// {
// 	t_command	*test;
// 	int			i;	
// 	const char	str[] = "I eat children :D";

// 	test = ft_calloc(1, sizeof(t_command));
// 	test->command = "cat";
// 	test->infile = "src/main.c";
// 	test->outfile = "test.c";
// 	i = 0;
// 	test->params = ft_calloc(PARAMS + 1, sizeof(char *));
// 	while (i < PARAMS)
// 		test->params[i++] = (char *)str;
// 	test->n_params = ft_count_elements(test->params);
// 	test->in_redirect = 2;
// 	test->fds[0] = open(test->infile, O_RDONLY | O_APPEND);
// 	test->fds[1] = open(test->infile, O_WRONLY, 0644);
// 	print_parser(test);
// 	return (0);
// }

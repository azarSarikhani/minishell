/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:53:04 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/09 11:53:04 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_paths(char ***paths, char *raw_path, char *cmd_name)
{
	size_t	len;

	if (paths)
	{
		len = ft_count_elements(*paths);
		ft_free_array(paths, len);
	}
	if (raw_path)
		ft_free(raw_path);
	if (cmd_name)
		ft_free(cmd_name);
}

static void	find_path(char **path, char **cmd_name)
{
	size_t	i;
	size_t	len;
	char	**paths;
	char	*raw_path;
	char	*test_path;

	i = 0;
	paths = ft_split(*path, ':');
	len = ft_count_elements(paths);
	while (i < len)
	{
		raw_path = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(raw_path, *cmd_name);
		if (access(test_path, X_OK) == 0)
		{
			ft_free_paths(&paths, raw_path, *cmd_name);
			*cmd_name = test_path;
			return ;
		}
		ft_free(raw_path);
		ft_free(test_path);
		i++;
	}
	ft_free_paths(&paths, NULL, NULL);
	return ;
}

int	get_exe_path(t_env **env, t_command *command)
{
	char	*path;

	while (command)
	{
		if (!is_builtin(command))
		{
			path = find_value(env, "PATH");
			if (path && command->command && command->command[0])
				find_path(&path, &(command->command));
		}
		command = command->next;
	}
	return (0);
}

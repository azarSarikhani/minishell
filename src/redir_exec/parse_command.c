/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/02/12 15:57:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_paths(char ***paths, char *raw_path)
{
	size_t	len;

	if (paths)
	{
		len = count_elements(*paths);
		ft_free_array(paths, len);
	}
	if (raw_path)
		ft_free(raw_path);
}

static char	*find_path(char **path, char **cmd_name)
{
	size_t	i;
	size_t	len;
	char	**paths;
	char	*raw_path;
	char	*test_path;

	i = 0;
	paths = ft_split(*path, ':');
	len = count_elements(paths);
	while (i < len)
	{
		raw_path = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(raw_path, *cmd_name);
		if (access(test_path, X_OK) == 0)
		{
			ft_free_paths(&paths, raw_path);
			return (test_path);
		}
		ft_free(raw_path);
		ft_free(test_path);
		i++;
	}
	ft_free_paths(&paths, NULL);
	return (ft_strdup(*cmd_name));
}

char	*get_exe_path(t_env **env, t_command *command)
{
	char	*path;
	char	*exe_path;
	size_t	i;

	i = -1;
	if (!find_built_in(command, &env))
	{
		path = find_env(env, "PATH", 0)->value;
		exe_path = find_path(&path, &(command->command));
		if (exe_path)
			return (exe_path);
	}
	return (NULL);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 14:05:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(t_command *cmd)
{
	char	*error_msg;

	error_msg = ft_strjoin("cd: ", cmd->params[1]);
	if (!error_msg)
	{
		ft_error(ENOMEM, "");
		ft_clear_everything(g_info);
		exit(ENOMEM);
	}
	ft_error(ENOENT, error_msg);
	free(error_msg);
}

int	ft_cd(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	cur_dir[PATH_MAX];

	if (!cmd->params[1] || out_fd < 0)
		return (EXIT_FAILURE);
	if (chdir(cmd->params[1]))
	{
		cd_error(cmd);
		return (EXIT_FAILURE);
	}
	oldpwd = find_env(env, "OLDPWD", 0);
	pwd = find_env(env, "PWD", 0);
	if (!oldpwd)
		add_env(env, new_env("OLDPWD", pwd->value));
	else
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
	}
	pwd->value = ft_strdup(getcwd(cur_dir, PATH_MAX));
	return (EXIT_SUCCESS);
}

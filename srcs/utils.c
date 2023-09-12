/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/12 22:11:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

char	*executable(char *cmd, char *path[])
{
	int		i;
	char	*temp;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (path && path[i])
	{
		temp = ft_joinpath(path[i++], cmd);
		if (!temp)
			return (NULL);
		if (!access(temp, X_OK))
			return (temp);
		free(temp);
	}
	return (NULL);
}

char	**get_path(char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(&envp[i][5], ':'));
}

int	exec(char *cmd, char *executor, char *envp[], char *env_path[])
{
	int		ret;
	size_t	i;
	char	*path;
	char	**args;

	args = cmdline_split(cmd);
	if (!args)
		return (-1);
	path = executable(args[0], env_path);
	if (!path)
		return (-1);
	free(args[0]);
	args[0] = executor;
	ret = execve(path, args, envp);
	i = 1;
	while (args[i])
		free(args[i++]);
	free(args);
	return (ret);
}

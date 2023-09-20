/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:07:45 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 20:42:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char	*executable(char *cmd, char *path[])
{
	char	*temp;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		perror(cmd);
	}
	else
	{
		while (path && *path)
		{
			temp = ft_joinpath(*path++, cmd);
			if (!temp || !access(temp, X_OK))
				return (temp);
			free(temp);
		}
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	return (NULL);
}

pid_t	eval(char *cmd, t_eval *config)
{
	pid_t	ret;
	char	*path;
	char	**head;
	char	**args;

	args = cmdline_split(cmd);
	if (!args)
		return (-1);
	path = executable(args[0], config->path);
	if (path)
		ret = execute(path, args, config->envp, &config->execute_var);
	else
		ret = -1;
	head = args;
	while (*args)
		free(*args++);
	free(*args);
	free(head);
	free(path);
	return (ret);
}

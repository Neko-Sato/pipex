/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:07:45 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/23 08:20:18 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	executable(char *cmd, char *path[], char **filename)
{
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
		{
			*filename = ft_strdup(cmd);
			return (-!*filename);
		}
		perror(cmd);
	}
	else
	{
		while (path && *path)
		{
			*filename = ft_joinpath(*path++, cmd);
			if (!*filename || !access(*filename, X_OK))
				return (-!*filename);
			free(*filename);
		}
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	*filename = NULL;
	return (1);
}

// When -1				: error
// When 0				: not_found
// When greater than 0	: success
pid_t	eval(char *cmd, t_eval *config)
{
	pid_t	ret;
	char	*path;
	char	**head;
	char	**args;

	args = cmdline_split(cmd);
	if (!args)
		return (-1);
	ret = executable(args[0], config->path, &path);
	if (ret == 0)
		ret = execute(path, args, config->envp, &config->execute_var);
	else if (ret == 1)
		ret = 0;
	head = args;
	while (*args)
		free(*args++);
	free(*args);
	free(head);
	free(path);
	return (ret);
}

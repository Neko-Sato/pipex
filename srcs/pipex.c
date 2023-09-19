/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 03:15:24 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	pipex(t_pipex *var, char *envp[])
{
	t_eval	config;
	pid_t	pid;
	size_t	i;
	int		reader;
	int		writer;
	int		temp;

	config.envp = envp;
	config.path = get_path(envp);
	//
	pid = 0;
	i = var->len;
	temp = open(var->file2, O_WRCT, S_RUWUGO);
	//
	while (!pid)
	{
		pid = fork();
		//
		if (!pid)
		{
			i--;
			writer = temp;
			if (0 < i)
			{
				ft_pipe3(&temp, &reader);
				//
			}
			else
			{
				reader = open(var->file1, O_RDONLY);
				//
			}
			config.execute_var.stdin = reader;
			config.execute_var.stdout = writer;
			if (0 < i)
			{
				eval(var->cmds[i], &config);
				//
			}
			exit(0);
		}
	}
	waitpid(pid, NULL, 0);
	close(temp);
	free(config.path);
}

char	*executable(char *cmd, char *path[])
{
	char	*temp;

	if (!access(cmd, X_OK))
	{
		temp = ft_strdup(cmd);
		ft_excption("malloc", 1, !temp);
		return (temp);
	}
	else
	{
		while (path && *path)
		{
			temp = ft_joinpath(*path++, cmd);
			ft_excption("malloc", 1, !temp);
			if (!access(temp, X_OK))
				return (temp);
			free(temp);
		}
		return (NULL);
	}
}

pid_t	eval(char *cmd, t_eval *config)
{
	pid_t	ret;
	size_t	i;
	char	*path;
	char	**args;

	args = cmdline_split(cmd);
	ft_excption("malloc", 1, !args);
	path = executable(args[0], config->path);
	ft_excption(args[0], 1, !path);
	ret = execute(path, args, config->envp, &config->execute_var);
	ft_excption("fork", 1, ret == -1);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(path);
	return (ret);
}

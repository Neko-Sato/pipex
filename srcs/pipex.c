/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/16 05:00:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//	もっと納得のいくエラー処理とか
void	pipex(t_pipex *vars, char *envp[])
{
	t_eval	config;
	size_t	i;
	int		fd[3];
	pid_t	pid;

	config.envp = envp;
	config.path = get_path(envp);
	ft_excption("malloc", !config.path);
	i = 0;
	fd[0] = open(vars->file1, O_RDONLY);
	ft_excption("open", fd[0] == -1);
	while (++i)
	{
		if (i < vars->len)
			ft_pipe3(&fd[2], &fd[1]);
		else
			fd[1] = open(vars->file2, O_WRCT, S_RUWUGO);
		ft_excption("open or pipe", fd[1] == -1);
		ft_memcpy(config.stdio, fd, sizeof(int) * 2);
		pid = eval(vars->cmds[i - 1], &config);
		ft_excption("close", close(fd[0]) || close(fd[1]));
		if (i >= vars->len)
			break ;
		fd[0] = fd[2];
	}
	waitpid(pid, NULL, 0);
}

char	*executable(char *cmd, char *path[])
{
	char	*temp;

	if (!access(cmd, X_OK))
	{
		temp = ft_strdup(cmd);
		ft_excption("malloc", !temp);
		return (temp);
	}
	else
	{
		while (path && *path)
		{
			temp = ft_joinpath(*path++, cmd);
			ft_excption("malloc", !temp);
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
	ft_excption("malloc", !args);
	path = executable(args[0], config->path);
	if (path)
	{
		ret = execute(path, args, config->envp, config->stdio);
		ft_excption("fork", ret == -1);
	}
	else
	{
		ret = 0;
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(path);
	return (ret);
}

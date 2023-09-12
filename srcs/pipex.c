/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/12 12:15:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int	exec(char *cmd, char *executor, char *envp[], char *env_path[]);

int	pipex(t_pipex *vars, char *executor, char *envp[])
{
	char	**env_path;
	int		ret;
	int		input;
	int		output;
	int		fd[2];
	size_t	i;
	pid_t	pid;

	env_path = get_path(envp);
	i = 0;
	input = open(vars->file1, O_RDONLY);
	while (1)
	{
		if (i < vars->len - 1)
		{
			pipe(fd);
			output = fd[1];
		}
		else
			output = open(vars->file2, O_WRONLY);
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid)
		{
			ret = wait(NULL) != pid;
			if (i)
				exit(ret);
			return (ret);
		}
		setstdio(input, output);
		exec(vars->cmds[i], executor, envp, env_path);
		if (i < vars->len - 1)
			input = fd[0];
		else
			exit(0);
		i++;
	}
}

static int	exec(char *cmd, char *executor, char *envp[], char *env_path[])
{
	int		ret;
	size_t	i;
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
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



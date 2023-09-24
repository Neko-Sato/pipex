/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/24 15:01:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <libft.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	setstdio(int input, int output)
{
	dup2(input, STDIN_FILENO);
	if (STDIN_FILENO != input)
		close(input);
	dup2(output, STDOUT_FILENO);
	if (STDOUT_FILENO != output)
		close(output);
}

pid_t	execute(char *pathname, char *argv[], char *envp[], t_execute *var)
{
	pid_t	pid;

	if (!var->run_here)
		pid = fork();
	else
		pid = 0;
	if (!pid)
	{
		setstdio(var->stdin, var->stdout);
		pid = execve(pathname, argv, envp);
		if (!var->run_here)
			exit(EXIT_FAILURE);
	}
	return (pid);
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

int	newpipe(int *reader, int *writer)
{
	int	ret;
	int	fd[2];

	ret = pipe(fd);
	if (!ret)
	{
		*reader = fd[0];
		*writer = fd[1];
	}
	return (ret);
}

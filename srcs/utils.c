/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/16 00:36:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
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

pid_t	execute(char *pathname, char *argv[], char *envp[], int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		setstdio(fd[0], fd[1]);
		execve(pathname, argv, envp);
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

void	ft_pipe3(int *reader, int *writer)
{
	int	ret;
	int	fd[2];

	ret = pipe(fd);
	if (!ret)
	{
		*reader = fd[0];
		*writer = fd[1];
	}
	else
	{
		*reader = -1;
		*writer = -1;
	}
}

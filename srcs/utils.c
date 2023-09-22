/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/22 08:32:09 by hshimizu         ###   ########.fr       */
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

char	*nodupfilename(char *filename)
{
	char		*newfilename;
	unsigned	i;
	char		*i_str;

	i = 0;
	while (1)
	{
		i_str = ft_utoa(i);
		if (!i_str)
			return (NULL);
		newfilename = ft_strjoin(filename, i_str);
		free(i_str);
		if (!newfilename)
			return (NULL);
		if (access(newfilename, F_OK) == -1)
			break ;
		free(newfilename);
		if (i >= UINT_MAX)
			return (NULL);
	}
	return (newfilename);
}

void	ft_excption(char *s, int abort)
{
	if (!abort)
		return ;
	perror(s);
	exit(EXIT_FAILURE);
}
